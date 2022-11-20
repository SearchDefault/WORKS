#ifndef GENERAL_H
#define GENERAL_H

#ifdef _WIN32
#else
#define SD_BOTH 0
#include <sys/socket.h>
#endif

#include <iostream>
#include <queue>
#include <thread>
#include <chrono>
#include <mutex>
#include <future>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <any>
#include <cassert>
#include <atomic>
#include <functional>
#include <cstring>
#include <string>
#include <map>
#include <vector>

/// Sipmple TCP
namespace stcp {

#ifdef _WIN32 // Windows NT
typedef int SockLen_t;
typedef SOCKADDR_IN SocketAddr_in;
typedef SOCKET Socket;
typedef u_long ka_prop_t;
#else // POSIX
typedef socklen_t SockLen_t;
typedef struct sockaddr_in SocketAddr_in;
typedef int Socket;
typedef int ka_prop_t;
#endif

constexpr uint32_t LOCALHOST_IP = 0x0100007f;

enum class SocketStatus : uint8_t {
  connected = 0,
  err_socket_init = 1,
  err_socket_bind = 2,
  err_socket_connect = 3,
  disconnected = 4
};

enum class TaskStatus {
    in_q,
    completed
};

class Task {
public:
    template <typename FuncRetType, typename ...Args, typename ...FuncTypes>
    Task(FuncRetType(*func)(FuncTypes...), Args&&... args) :
        is_void{ std::is_void_v<FuncRetType> } {

        if constexpr (std::is_void_v<FuncRetType>) {
            void_func = std::bind(func, args...);
            any_func = []()->int { return 0; };
        }
        else {
            void_func = []()->void {};
            any_func = std::bind(func, args...);
        }
    }
    
    template <typename Func>
    Task(Func func) :
        is_void{ true } {

        void_func = std::bind(func);
        any_func = []()->int { return 0; };
    }

    void operator() () {
        void_func();
        any_func_result = any_func();
    }

    bool has_result() {
        return !is_void;
    }

    std::any get_result() const {
        assert(!is_void);
        assert(any_func_result.has_value());
        return any_func_result;
    }

private:
    std::function<void()> void_func;
    std::function<std::any()> any_func;
    std::any any_func_result;
    bool is_void;
};

struct TaskInfo {
    TaskStatus status = TaskStatus::in_q;
    std::any result;
};


class ThreadPool {
public:
    ThreadPool(const uint32_t num_threads) {
        threads.reserve(num_threads);
        for (uint32_t i = 0; i < num_threads; ++i) {
            threads.emplace_back(&ThreadPool::run, this);
        }
    }

    template <typename Func, typename ...Args, typename ...FuncTypes>
    uint64_t add_task(Func(*func)(FuncTypes...), Args&&... args) {

        const uint64_t task_id = last_idx++;

        std::unique_lock<std::mutex> lock(tasks_info_mtx);
        tasks_info[task_id] = TaskInfo();
        lock.unlock();

        std::lock_guard<std::mutex> q_lock(q_mtx);
        q.emplace(Task(func, std::forward<Args>(args)...), task_id);
        q_cv.notify_one();
        return task_id;
    }
    
    template <typename Func>
    uint64_t add_task(Func func) {

        const uint64_t task_id = last_idx++;

        std::unique_lock<std::mutex> lock(tasks_info_mtx);
        tasks_info[task_id] = TaskInfo();
        lock.unlock();

        std::lock_guard<std::mutex> q_lock(q_mtx);
        q.emplace(Task(func), task_id);
        q_cv.notify_one();
        return task_id;
    }

    void wait(const uint64_t task_id) {
        std::unique_lock<std::mutex> lock(tasks_info_mtx);
        tasks_info_cv.wait(lock, [this, task_id]()->bool {
            return task_id < last_idx && tasks_info[task_id].status == TaskStatus::completed;
        });
    }

    std::any wait_result(const uint64_t task_id) {
        std::unique_lock<std::mutex> lock(tasks_info_mtx);
        tasks_info_cv.wait(lock, [this, task_id]()->bool {
            return task_id < last_idx && tasks_info[task_id].status == TaskStatus::completed;
        });
        return tasks_info[task_id].result;
    }

    template<class T>
    void wait_result(const uint64_t task_id, T& value) {
        std::unique_lock<std::mutex> lock(tasks_info_mtx);
        tasks_info_cv.wait(lock, [this, task_id]()->bool {
            return task_id < last_idx && tasks_info[task_id].status == TaskStatus::completed;
        });
        value = std::any_cast<T>(tasks_info[task_id].result);
    }

    void wait_all() {
        std::unique_lock<std::mutex> lock(tasks_info_mtx);
        wait_all_cv.wait(lock, [this]()->bool { return cnt_completed_tasks == last_idx; });
    }

    bool calculated(const uint64_t task_id) {
        std::lock_guard<std::mutex> lock(tasks_info_mtx);
        return task_id < last_idx&& tasks_info[task_id].status == TaskStatus::completed;
    }
    
    uint32_t get_thread_count () { return threads.size (); }

    ~ThreadPool() {
        quite = true;
        q_cv.notify_all();
        for (uint32_t i = 0; i < threads.size(); ++i) {
            threads[i].join();
        }
    }

private:
    
    inline void garbage_collector ()
    {
        if ( !(cnt_completed_tasks % 1000) )
            tasks_info.clear ();
    }

    void run() {
        while (!quite) {
            std::unique_lock<std::mutex> lock(q_mtx);
            q_cv.wait(lock, [this]()->bool { return !q.empty() || quite; });

            if (!q.empty() && !quite) {
                std::pair<Task, uint64_t> task = std::move(q.front());
                q.pop();
                lock.unlock();

                task.first();

                std::lock_guard<std::mutex> lock(tasks_info_mtx);
                if (task.first.has_result()) {
                    tasks_info[task.second].result = task.first.get_result();
                }
                tasks_info[task.second].status = TaskStatus::completed;
                ++cnt_completed_tasks;
                
                garbage_collector ();
            }
            wait_all_cv.notify_all();
            tasks_info_cv.notify_all(); // notify for wait function
        }
    }

    std::vector<std::thread> threads;

    std::queue<std::pair<Task, uint64_t>> q;
    std::mutex q_mtx;
    std::condition_variable q_cv;

    std::unordered_map<uint64_t, TaskInfo> tasks_info;
    std::condition_variable tasks_info_cv;
    std::mutex tasks_info_mtx;

    std::condition_variable wait_all_cv;

    std::atomic<bool> quite{ false };
    std::atomic<uint64_t> last_idx{ 0 };
    std::atomic<uint64_t> cnt_completed_tasks{ 0 };
};

typedef std::vector<uint8_t> DataBuffer;

enum class SocketType : uint8_t {
  client_socket = 0,
  server_socket = 1
};

class TcpClientBase {
public:
  typedef SocketStatus status;
  virtual ~TcpClientBase() {};
  virtual status disconnect() = 0;
  virtual status getStatus() const = 0;
  virtual bool sendData(const void* buffer, const size_t size) const = 0;
  virtual DataBuffer loadData() = 0;
  virtual uint32_t getHost() const = 0;
  virtual uint16_t getPort() const = 0;
  virtual SocketType getType() const = 0;
};

#ifdef _WIN32 // Windows NT
namespace {
class _WinSocketIniter {
  static WSAData w_data;
public:
  _WinSocketIniter() {
    WSAStartup(MAKEWORD(2, 2), &w_data)
  }

  ~_WinSocketIniter() {
    WSACleanup()
  }
};

static inline _WinSocketIniter _winsock_initer;
}
#endif

}

#endif // GENERAL_H
