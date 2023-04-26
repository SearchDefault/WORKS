#ifndef __RENDERER_HPP__
#define __RENDERER_HPP__

// Links ImGUI ImPlot and Backends heders
#include "../ImGUI/imgui.h"
#include "../ImPlot/implot.h"
#include "../Backends/imgui_impl_sdl.h"
#include "../Backends/imgui_impl_opengl3.h"

#include "../Network/TcpServer.h"
#include "FileManager.hpp"
#include "Kalman.hpp"

#include "../ImGuiFileDialog/ImGuiFileDialog.h"

#include <cmath>

// Links <SDL>
//#include <SDL.h>
#include <SDL2/SDL.h>
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <SDL2/SDL_opengles2.h>
#else
//#include <SDL_opengl.h>
#include <SDL2/SDL_opengl.h>
#endif

#ifdef _WIN32
#include <windows.h>
#endif

namespace Renderer
{
    using namespace stcp;
    
    struct ExampleAppLog
    {
        ImGuiTextBuffer     Buf;
        ImGuiTextFilter     Filter;
        ImVector<int>       LineOffsets; // Index to lines offset. We maintain this with AddLog() calls.
        bool                AutoScroll;  // Keep scrolling if already at the bottom.
        bool                ServerStartStop = false;
        bool                Start = false;
        bool                Stop = false;
        bool                SaveInFile = false;
        
        ExampleAppLog()
        {
            AutoScroll = true;
            Clear();
        }

        void    Clear()
        {
            Buf.clear();
            LineOffsets.clear();
            LineOffsets.push_back(0);
        }

        void    AddLog(const char* fmt, ...) IM_FMTARGS(2)
        {
            int old_size = Buf.size();
            va_list args;
            va_start(args, fmt);
            Buf.appendfv(fmt, args);
            va_end(args);
            for (int new_size = Buf.size(); old_size < new_size; old_size++)
                if (Buf[old_size] == '\n')
                    LineOffsets.push_back(old_size + 1);
        }

        void    Draw(const char* title, bool* p_open = NULL)
        {
            if (!ImGui::Begin(title, p_open))
            {
                ImGui::End();
                return;
            }

            // Options menu
            if (ImGui::BeginPopup("Options"))
            {
                ImGui::Checkbox("Auto-scroll", &AutoScroll);
                ImGui::EndPopup();
            }

            // Main window
            if (ImGui::Button("Options"))
                ImGui::OpenPopup("Options");
            ImGui::SameLine();
            bool clear = ImGui::Button("Clear");
            ImGui::SameLine();
            bool copy = ImGui::Button("Copy");
            ImGui::SameLine();
            ImGui::Checkbox("Start Server", &ServerStartStop);
            ImGui::SameLine();
            ImGui::Checkbox("Save File", &SaveInFile);
            ImGui::SameLine();
            Start = ImGui::Button("Start");
            ImGui::SameLine();
            Stop = ImGui::Button("Stop");
            ImGui::SameLine();
            Filter.Draw("Filter", -100.0f);

            ImGui::Separator();
            ImGui::BeginChild("scrolling", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);

            if (clear)
                Clear();
            if (copy)
                ImGui::LogToClipboard();

            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
            const char* buf = Buf.begin();
            const char* buf_end = Buf.end();
            if (Filter.IsActive())
            {
                for (int line_no = 0; line_no < LineOffsets.Size; line_no++)
                {
                    const char* line_start = buf + LineOffsets[line_no];
                    const char* line_end = (line_no + 1 < LineOffsets.Size) ? (buf + LineOffsets[line_no + 1] - 1) : buf_end;
                    if (Filter.PassFilter(line_start, line_end))
                        ImGui::TextUnformatted(line_start, line_end);
                }
            }
            else
            {
                ImGuiListClipper clipper;
                clipper.Begin(LineOffsets.Size);
                while (clipper.Step())
                {
                    for (int line_no = clipper.DisplayStart; line_no < clipper.DisplayEnd; line_no++)
                    {
                        const char* line_start = buf + LineOffsets[line_no];
                        const char* line_end = (line_no + 1 < LineOffsets.Size) ? (buf + LineOffsets[line_no + 1] - 1) : buf_end;
                        ImGui::TextUnformatted(line_start, line_end);
                    }
                }
                clipper.End();
            }
            ImGui::PopStyleVar();

            if (AutoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
                ImGui::SetScrollHereY(1.0f);

            ImGui::EndChild();
            ImGui::End();
        }
    };
    
    struct ScrollingBuffer
    {
        int MaxSize;
        int Offset;
        ImVector<ImVec2> Data;
        ScrollingBuffer(int max_size = 2000)
        {
            MaxSize = max_size;
            Offset  = 0;
            Data.reserve(MaxSize);
        }
        void AddPoint(float x, float y)
        {
            if (Data.size() < MaxSize)
                Data.push_back(ImVec2(x,y));
            else {
                Data[Offset] = ImVec2(x,y);
                Offset =  (Offset + 1) % MaxSize;
            }
        }
        void Erase()
        {
            if (Data.size() > 0) {
                Data.shrink(0);
                Offset  = 0;
            }
        }
    };

    class WindowContext
    {
        const char* glsl_version;

        SDL_DisplayMode DM;
        SDL_WindowFlags window_flags;
        SDL_Window* window;
        SDL_GLContext gl_context;

        ImGuiContext* imGUI_context;
        SDL_Event event;

        // Server
        std::shared_ptr<TcpServer> server;

        // FileManager
        std::shared_ptr<FileManager> fman;
        
        // Logger
        ExampleAppLog log;
        
        std::vector<std::string> textData;
        
        // For Plot
        ScrollingBuffer gyroX, gyroY, gyroZ, accX, accY, accZ;
        float t = 0;

        // DELETE
        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f );

        void init_all    ( void );
        void SDL_init    ( void );
        void ImGUI_init  ( void );
        void ImPlot_init ( void );
        void Server_init ( void );

        void clean_data  ( void );

    public:
        WindowContext ();
        virtual ~WindowContext ();

        WindowContext(WindowContext const&) = delete;
        void operator = (WindowContext const&) = delete;

        void Update      ( bool& done );
        void Render      ( bool& done, bool& show_plot_window, bool& show_demo_window, bool& show_logger, bool& show_data_plot );
    };
}

#endif//__RENDERER_HPP__
