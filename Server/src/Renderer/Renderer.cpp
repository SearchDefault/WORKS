#include "Renderer.hpp"

#define RAD_TO_DEG 180/M_PI

namespace Renderer
{
    std::string getHostStr(const TcpServer::Client& client)
    {
        uint32_t ip = client.getHost ();
        return std::string() + std::to_string(int(reinterpret_cast<char*>(&ip)[0])) + '.' +
                std::to_string(int(reinterpret_cast<char*>(&ip)[1])) + '.' +
                std::to_string(int(reinterpret_cast<char*>(&ip)[2])) + '.' +
                std::to_string(int(reinterpret_cast<char*>(&ip)[3])) + ':' +
                std::to_string( client.getPort () );
    }

    WindowContext::WindowContext ()
    {
        init_all ();
    }

    WindowContext::~WindowContext ()
    {
        clean_data ();
    }

    void WindowContext::init_all ( void )
    {
        SDL_init ();
        ImGUI_init ();
        ImPlot_init ();
        Server_init ();
    }

    void WindowContext::SDL_init ( void )
    {
        #if defined(IMGUI_IMPL_OPENGL_ES2)
        // GL ES 2.0 + GLSL 100
        this -> glsl_version = "#version 100";
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
        #elif defined(__APPLE__)
        // GL 3.2 Core + GLSL 150
        this -> glsl_version = "#version 150";
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG); // Always required on Mac
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
        #else
        // GL 3.0 + GLSL 130
        this -> glsl_version = "#version 130";
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
        #endif

        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
        {
            std::printf("Error: %s\n", SDL_GetError());
            clean_data ();
            exit ( EXIT_FAILURE );
        }

        SDL_GetCurrentDisplayMode(0, &DM);

        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
        SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
        
        this -> window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
        
        this -> window = SDL_CreateWindow("Server Sensor Device", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, DM.w, DM.h, window_flags);
        
        this -> gl_context = SDL_GL_CreateContext(window);
        
        SDL_GL_MakeCurrent(window, gl_context);
        SDL_GL_SetSwapInterval(1); // Enable vsync
    }

    void WindowContext::ImGUI_init  ( void )
    {
        IMGUI_CHECKVERSION();
        this -> imGUI_context = ImGui::CreateContext();

        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
        //io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
        //io.ConfigViewportsNoAutoMerge = true;
        //io.ConfigViewportsNoTaskBarIcon = true;

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsClassic();

        // Setup Platform/Renderer backends
        ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
        ImGui_ImplOpenGL3_Init(glsl_version);
    }

    void WindowContext::ImPlot_init ( void )
    {
        ImPlot::CreateContext();
    }

    void WindowContext::Server_init ( void )
    {
        this -> fman = std::make_shared<FileManager> ( "002.txt" );
        
        // Create Server Context
        this -> server = std::unique_ptr<TcpServer> ( new TcpServer (
            9001,
            
            {1, 1, 1}, // Keep alive{idle:1s, interval: 1s, pk_count: 1}

            [this](DataBuffer data, TcpServer::Client& client){ // Data handler
                //std::cout << "Client "<< getHostStr(client) <<" send data [ " << data.size() << " bytes ]: " << data.data() << '\n';
                log.AddLog ( "Client %s send data [ %ld bytes ]: %s\n", getHostStr(client).c_str(), data.size(), reinterpret_cast<char*> ( data.data () ) );
                
                int32_t device, time;
                int16_t dataGyroX, dataGyroY, dataGyroZ, dataAccX, dataAccY, dataAccZ;
                int num = sscanf ( reinterpret_cast<char*> ( data.data () ), "{\"D\":%d,\"T\":%d,\"G\":{\"X\":%hd,\"Y\":%hd,\"Z\":%hd},\"A\":{\"X\":%hd,\"Y\":%hd,\"Z\":%hd}", &device, &time, &dataGyroX, &dataGyroY, &dataGyroZ, &dataAccX, &dataAccY, &dataAccZ );
                
                //fman -> SaveInFile ( reinterpret_cast<char*> ( data.data () ) );
                
                if ( num == 8 )
                {
                    t = 0.001f * time;
                    gyroX.AddPoint ( t, dataGyroX );
                    gyroY.AddPoint ( t, dataGyroY );
                    gyroZ.AddPoint ( t, dataGyroZ );
                    
                    accX.AddPoint ( t, dataAccX );
                    accY.AddPoint ( t, dataAccY );
                    accZ.AddPoint ( t, dataAccZ );
                }
            },

            [this](TcpServer::Client& client) { // Connect handler
                //std::cout << "Client " << getHostStr(client) << " connected\n";
                log.AddLog ( "Client %s connected\n", getHostStr(client).c_str() );
            },

            [this](TcpServer::Client& client) { // Disconnect handler
                //std::cout << "Client " << getHostStr(client) << " disconnected\n";
                log.AddLog ( "Client %s disconnected\n", getHostStr(client).c_str() );
            },

            std::thread::hardware_concurrency() // Thread pool size
        ));
    }

    void WindowContext::clean_data  ( void )
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImPlot::DestroyContext();
        ImGui::DestroyContext();

        SDL_GL_DeleteContext(gl_context);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    void WindowContext::Update ( bool& done )
    {
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT)
                done = true;
            if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window))
                done = true;
            if ( ( event.key.keysym.mod & KMOD_LCTRL ) && event.key.keysym.sym == SDLK_q )
                done = true;
        }
    }

    void WindowContext::Render      ( bool& done, bool& show_plot_window, bool& show_demo_window, bool& show_logger, bool& show_data_plot )
    {
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);
        
        if (show_plot_window)
            ImPlot::ShowDemoWindow(&show_plot_window);

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
        {
            ImGui::Begin("Main Menu");                          // Create a window called "Hello, world!" and append into it.

            if ( !static_cast<int> ( server -> getStatus() ) )
                ImGui::Text("Server is: %s", "Up" );            // Display some text (you can use a format strings too)
            else
                ImGui::Text("Server is: %s", "Down" );
            
            ImGui::Text("Server listen on port: %d", server -> getPort() );
            ImGui::Text("Server handling thread pool size: %d", server -> getThreadPool().get_thread_count() );
            
            ImGui::Checkbox("Demo Window", &show_demo_window);
            ImGui::Checkbox("Plot Window", &show_plot_window);
            ImGui::Checkbox("Server Logger", &show_logger);
            ImGui::Checkbox("Data Plot", &show_data_plot);
            
            ImGui::Separator();
            
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }
        
        // Logger Draw
        if (show_logger)
        {
            ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiCond_FirstUseEver);
            ImGui::Begin("Logger", &show_logger);
            ImGui::End();
            
            if ( log.ServerStartStop && server -> getStatus() == TcpServer::status::close )
            {
                using namespace std::chrono_literals;
                try
                {
                    //Start server
                    if(server -> start() == TcpServer::status::up) {
                        // std::cout<<"Server listen on port: " << server -> getPort() << std::endl
                        //         <<"Server handling thread pool size: " << server -> getThreadPool().getThreadCount() << std::endl;
                    }
                    else
                    {
                        std::cout<<"Server start error! Error code:"<< int(server -> getStatus()) <<std::endl;
                        exit ( EXIT_FAILURE );
                    }

                } catch(std::exception& except)
                {
                    std::cerr << except.what();
                    exit ( EXIT_FAILURE );
                }
            }
            
            if ( !log.ServerStartStop && server -> getStatus() == TcpServer::status::up )
                server -> stop ();

            // Actually call in the regular Log helper (which will Begin() into the same window as we just did)
            log.Draw("Logger", &show_logger);
        }
        
        //Data plot
        if (show_data_plot)
        {
            ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiCond_FirstUseEver);
            
            ImGui::Begin("Data Plot", &show_data_plot);
            ImGui::Text("Click to button to open file");
            
            // Always center this window when appearing
            ImVec2 center = ImGui::GetMainViewport()->GetCenter();
            ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
            
            static float _low = 0.3f, _hight = 0.45f;
            static int ampl = 4.0;
            ImGui::InputFloat("low", &_low, -1.0f, 1.0f, "%.3f");
            ImGui::InputFloat("hight", &_hight, -1.0f, 1.0f, "%.3f");
            ImGui::InputInt("ampl", &ampl, 0, 10);
            
            bool openFile = false;
            if ( ImGui::Button ( "Open" ) )
                ImGui::OpenPopup ( "Open File" );
            if ( ImGui::BeginPopupModal ( "Open File", NULL, ImGuiWindowFlags_AlwaysAutoResize ) )
            {
                ImGui::Text("Please enter the namefile, like (text.txt)");

                ImGui::Separator();
                
                static char fileName[128];
                if ( ImGui::InputTextWithHint( "(<--Take Enter to apply changes)", "enter file name here", fileName, IM_ARRAYSIZE(fileName), ImGuiInputTextFlags_EnterReturnsTrue ) )
                    fman -> Open ( fileName );
                
                ImGui::Separator();
                
                if (ImGui::Button("Ok", ImVec2(220, 20)))
                {
                    openFile = true;
                    ImGui::CloseCurrentPopup();
                }
                
                ImGui::SameLine();
                
                if (ImGui::Button("Close", ImVec2(220, 20)))
                    ImGui::CloseCurrentPopup();
                    
                ImGui::EndPopup();
            }
            
            static ImVector<ImVec2> _accX;
            static ImVector<ImVec2> _accY;
            static ImVector<ImVec2> _accZ;
            
            static ImVector<ImVec2> _gyroX;
            static ImVector<ImVec2> _gyroY;
            static ImVector<ImVec2> _gyroZ;
            
            static ImVector<ImVec2> visual;
            
            if ( openFile )
            {
                textData = fman -> ReadInFile ();
                
                if ( !visual.empty () )
                    visual.clear ();
                
                if ( !_gyroX.empty () || !_gyroY.empty () || !_gyroZ.empty () )
                {
                    _gyroX.clear ();
                    _gyroY.clear ();
                    _gyroZ.clear ();
                }
                
                if ( !_accX.empty () || !_accY.empty () || !_accZ.empty () )
                {
                    _accX.clear ();
                    _accY.clear ();
                    _accZ.clear ();
                } 
                
                for ( auto line : textData )
                {
                    int32_t device, time;
                    int16_t dataGyroX, dataGyroY, dataGyroZ, dataAccX, dataAccY, dataAccZ;
                    float fdataAccX, fdataAccY, fdataAccZ;
                    //int num = sscanf ( line.c_str (), "{\"D\":%d,\"T\":%d,\"G\":{\"X\":%hd,\"Y\":%hd,\"Z\":%hd},\"A\":{\"X\":%hd,\"Y\":%hd,\"Z\":%hd}", &device, &time, &dataGyroX, &dataGyroY, &dataGyroZ, &dataAccX, &dataAccY, &dataAccZ );
                    
                    //1T0X-42Y-179Z-179X7308Y898Z10644
                    int num = sscanf ( line.c_str (), "%dT%dX%hdY%hdZ%hdX%hdY%hdZ%hd", &device, &time, &dataGyroX, &dataGyroY, &dataGyroZ, &dataAccX, &dataAccY, &dataAccZ );
                    
                    if ( num == 8 )
                        if ( device == 1 )
                        {
                            if ( dataGyroX > 32768 )
                                dataGyroX -= 65535;
                            dataGyroX /= 65.5;
                            
                            if ( dataGyroY > 32768 )
                                dataGyroY -= 65535;
                            dataGyroY /= 65.5;
                            
                            if ( dataGyroZ > 32768 )
                                dataGyroZ -= 65535;
                            dataGyroZ /= 65.5;
                            
                            if ( dataAccX > 32768 )
                                dataAccX -= 65535;
                            fdataAccX = static_cast<float> ( dataAccX ) / 8192;
                            
                            if ( dataAccY > 32768 )
                                dataAccY -= 65535;
                            fdataAccY = static_cast<float> ( dataAccY ) / 8192;
                            
                            if ( dataAccZ > 32768 )
                                dataAccZ -= 65535;
                            fdataAccZ = static_cast<float> ( dataAccZ ) / 8192;
                            
                            time /= 1000;   
                            
                            _gyroX.push_back ( ImVec2 ( time, dataGyroX ) );
                            _gyroY.push_back ( ImVec2 ( time, dataGyroY ) );
                            _gyroZ.push_back ( ImVec2 ( time, dataGyroZ ) );
                            
                            _accX.push_back ( ImVec2 ( time, fdataAccX ) );
                            _accY.push_back ( ImVec2 ( time, fdataAccY ) );
                            _accZ.push_back ( ImVec2 ( time, fdataAccZ ) );
                        }
                }
                
                // Kalman Relialisation
//                 {
//                     Kalman kalmanX;
//                     Kalman kalmanY;
//                     Kalman kalmanZ;
//                     
//                     double accXangle;
//                     double accYangle;
//                     double accZangle;
//                     
//                     double gyroXangle = 180;
//                     double gyroYangle = 180;
//                     double gyroZangle = 180;
//                     double compAngleX = 180;
//                     double compAngleY = 180;
//                     double compAngleZ = 180;
//                     double kalAngleX;
//                     double kalAngleY;
//                     double kalAngleZ;
//                     
//                     const int ANGLES_COUNT = _accX.size ();
//                     double xAngles[ANGLES_COUNT];
//                     double yAngles[ANGLES_COUNT];
//                     double zAngles[ANGLES_COUNT];
//                     
//                     kalmanX.setAngle(180);
//                     kalmanY.setAngle(180);
//                     kalmanZ.setAngle(180);
//                     
//                     for ( int i = 0; i < ANGLES_COUNT; i++ )
//                     {
//                         xAngles[i] = gyroXangle;
//                         yAngles[i] = gyroYangle;
//                         zAngles[i] = gyroZangle;
//                     }
//                     
//                     for (int i = 0; i < ANGLES_COUNT - 1; i++)
//                     {
//                         xAngles[i] = xAngles[i + 1];
//                         yAngles[i] = yAngles[i + 1];
//                         zAngles[i] = zAngles[i + 1];
//                     }
//                     xAngles[ANGLES_COUNT - 1] = gyroXangle;
//                     yAngles[ANGLES_COUNT - 1] = gyroYangle;
//                     zAngles[ANGLES_COUNT - 1] = gyroZangle;
//                     
//                     double expectationX = 0.0;
//                     double expectationY = 0.0;
//                     double expectationZ = 0.0;
//                     
//                     for (int i = 0; i < ANGLES_COUNT; i++)
//                     {
//                         expectationX += xAngles[i];
//                         expectationY += yAngles[i];
//                         expectationZ += zAngles[i];
//                     }
//                     expectationX /= ANGLES_COUNT;
//                     expectationY /= ANGLES_COUNT;
//                     expectationZ /= ANGLES_COUNT;
//                     
//                     double varianceX = 0.0;
//                     double varianceY = 0.0;
//                     double varianceZ = 0.0;
//                     for (int i = 0; i < ANGLES_COUNT; i++)
//                     {
//                         varianceX += xAngles[i] * xAngles[i];
//                         varianceY += yAngles[i] * yAngles[i];
//                         varianceZ += zAngles[i] * zAngles[i];
//                     }
//                     varianceX -= ANGLES_COUNT * expectationX * expectationX;
//                     varianceY -= ANGLES_COUNT * expectationY * expectationY;
//                     varianceZ -= ANGLES_COUNT * expectationZ * expectationZ;
//                     
//                     varianceX /= ANGLES_COUNT - 1;
//                     varianceY /= ANGLES_COUNT - 1;
//                     varianceZ /= ANGLES_COUNT - 1;
//                     
//                     kalmanX.setQangle(varianceX);
//                     kalmanY.setQangle(varianceY);
//                     kalmanZ.setQangle(varianceZ);
//                     
//                     //
//                     for ( int i = 0; i < ANGLES_COUNT; i++ )
//                     {
//                         kalmanX.setQangle(0.05);
//                         kalmanY.setQangle(0.05);
//                         kalmanZ.setQangle(0.05);
//                         
//                         accYangle = (atan2(_accX[i].y,_accZ[i].y)+M_PI)*RAD_TO_DEG;
//                         accXangle = (atan2(_accY[i].y,_accZ[i].y)+M_PI)*RAD_TO_DEG;
//                         accZangle = (atan2(_accX[i].y,_accY[i].y)+M_PI)*RAD_TO_DEG;
//                         
//                         double gyroXrate = (double)_gyroX[i].y/131.0;
//                         double gyroYrate = -((double)_gyroY[i].y/131.0);
//                         double gyroZrate = -((double)_gyroZ[i].y/131.0);
//                         
//                         gyroXangle += gyroXrate*((double)(_gyroX[i].x));
//                         gyroYangle += gyroYrate*((double)(_gyroY[i].x));
//                         gyroZangle += gyroZrate*((double)(_gyroZ[i].x));
//                         
//                         compAngleX = (0.9*(compAngleX+(gyroXrate*(double)(_gyroX[i].y))))+(0.1*accXangle);
//                         compAngleY = (0.9*(compAngleY+(gyroYrate*(double)(_gyroY[i].y))))+(0.1*accYangle);
//                         compAngleZ = (0.9*(compAngleZ+(gyroZrate*(double)(_gyroZ[i].y))))+(0.1*accZangle);
//                         
//                         kalAngleX = kalmanX.getAngle(accXangle, gyroXrate, (double)(_gyroX[i].y));
//                         kalAngleY = kalmanY.getAngle(accYangle, gyroYrate, (double)(_gyroY[i].y));
//                         kalAngleZ = kalmanZ.getAngle(accZangle, gyroZrate, (double)(_gyroZ[i].y));
//                         
//                         std::printf("gyroX: ");
//                         std::printf("%g",accXangle);std::printf("\t");
//                         std::printf("gyroY: ");
//                         std::printf("%g",accYangle);std::printf("\t");
//                         std::printf("gyroZ: ");
//                         std::printf("%g",accZangle);std::printf("\t");
//                         std::printf("accX: ");
//                         std::printf("%g",gyroXangle);std::printf("\t");
//                         std::printf("accY: ");
//                         std::printf("%g",gyroYangle);std::printf("\t");
//                         std::printf("accZ: ");
//                         std::printf("%g",gyroZangle);std::printf("\t");
//                         std::printf("compX: ");
//                         std::printf("%g",compAngleX);std::printf("\t");
//                         std::printf("compY: ");
//                         std::printf("%g",compAngleY);std::printf("\t");
//                         std::printf("compZ: ");
//                         std::printf("%g",compAngleZ);std::printf("\t");
//                         std::printf("KalmX: ");
//                         std::printf("%g",kalAngleX);std::printf("\t");
//                         std::printf("KalmY ");
//                         std::printf("%g",kalAngleY);std::printf("\t");
//                         std::printf("KalmZ ");
//                         std::printf("%g",kalAngleZ);std::printf("\t");
//                         std::printf("QangleX: ");
//                         std::printf("%g",kalmanX.getQangle());std::printf("\t");
//                         std::printf("QangleY ");
//                         std::printf("%g",kalmanY.getQangle());std::printf("\t");
//                         std::printf("QangleZ ");
//                         std::printf("%g",kalmanZ.getQangle());std::printf("\n");
//                     }
//                }
                
                // Find Start Lockal Max
                float low = _accY[0].y;
                bool wait = false;
                int last_max;
                ImVector<int> samp_last_max;
                for ( int i = 1; i < _accY.size () - 1; i++ )
                {
                    if (_accY[i-1].y < _accY[i].y && _accY[i].y > _accY[i+1].y && _accY[i].y > low + 0.05 && _accY[i].y < low + 0.1 && !wait )
                    {
                        //std::cout << _accY[i].x << std::endl;
                        last_max = _accY[i].x;
                        samp_last_max.push_back(last_max);
                        wait = true;
                        //visual.push_back ( ImVec2 ( _accY[i].x, ampl ) );
                    }
                    else
                    {
                        if ( low > _accY[0].y + 0.01 && low < _accY[0].y + 0.03 )
                            low = _accY[i].y;
                        //visual.push_back ( ImVec2 ( _accY[i].x, _accY[i].y ) );
                        
                        if ( _accY[i].x - last_max >= 1100 )
                            wait = false;
                    }
                }
                
                for ( auto item : samp_last_max )
                    std::cout << item << std::endl;
                
                // Fase Step Analising
                bool start = false;
                for ( int i = 0, j = 0, c = 1000; i < _accY.size () - 1; i++ )
                {
                    if ( _accY[i].x == samp_last_max[j] )
                    {
                        start = true;
                        
                        if ( j != samp_last_max.size () - 1 )
                            j++;
                    }
                    else
                        if ( !start )
                            visual.push_back ( ImVec2 ( _accY[i].x, _accY[i].y ) );
                    
                    if ( start )
                    {
                        if ( _accY[i].y >= _low && _accY[i].y <= _hight )
                            visual.push_back ( ImVec2 ( _accY[i].x, _accY[i].y ) );
                        else
                            visual.push_back ( ImVec2 ( _accY[i].x, ampl ) );
                        
                        if ( samp_last_max[j] - c == _accY[i].x  )
                            start = false;
                    }
                }
                
                // for ( auto item : visual )
                //     std::cout << item.x << " " << item.y << std::endl;
                
                // Algorim to CreateVisualization
                // for ( int i = 0; i < _accY.size (); i++ )
                // {
                //     if ( _accY[i].y >= _low && _accY[i].y <= _hight )
                //         visual.push_back ( ImVec2 ( _accY[i].x, _accY[i].y ) );
                //     else
                //         visual.push_back ( ImVec2 ( _accY[i].x, ampl ) );
                // }
            }
            
            static bool GyroY_ImAxis_Y2 = false, GyroZ_ImAxis_Y3 = false;
            
            ImGui::Checkbox("GyroY ImAxis_Y2", &GyroY_ImAxis_Y2); ImGui::SameLine();
            ImGui::Checkbox("GyroZ ImAxis_Y3", &GyroZ_ImAxis_Y3);
            
            if ( ImPlot::BeginPlot("GyroPlot", ImVec2(-1,600)) )
            {
                ImPlot::SetupAxes ( "t, ms", "GyroX, degrees/ms", ImPlotAxisFlags_AutoFit, ImPlotAxisFlags_AutoFit );
                ImPlot::SetupAxesLimits(-100, 100, 0, 100000);
                
                if ( GyroY_ImAxis_Y2 )
                {
                    ImPlot::SetupAxis ( ImAxis_Y2, "GyroY, degrees/ms", ImPlotAxisFlags_AutoFit | ImPlotAxisFlags_AuxDefault );
                    ImPlot::SetupAxisLimits(ImAxis_Y2, -200, 200);
                }
                
                if ( GyroZ_ImAxis_Y3 )
                {
                    ImPlot::SetupAxis ( ImAxis_Y3, "GyroZ, degrees/ms", ImPlotAxisFlags_AutoFit | ImPlotAxisFlags_AuxDefault );
                    ImPlot::SetupAxisLimits(ImAxis_Y3, -200, 200);
                }

                if ( !_gyroX.empty() && !_gyroY.empty() && !_gyroZ.empty() )
                {
                    ImPlot::SetAxes(ImAxis_X1, ImAxis_Y1);
                    ImPlot::PlotLine ( "Gyro X", &_gyroX[0].x, &_gyroX[0].y, _gyroX.size(), 0, 0, sizeof(ImVec2) );
                    
                    if ( GyroY_ImAxis_Y2 )
                        ImPlot::SetAxes(ImAxis_X1, ImAxis_Y2);
                    ImPlot::PlotLine ( "Gyro Y", &_gyroY[0].x, &_gyroY[0].y, _gyroY.size(), 0, 0, sizeof(ImVec2) );
                    
                    if ( GyroZ_ImAxis_Y3 )
                        ImPlot::SetAxes(ImAxis_X1, ImAxis_Y3);
                    ImPlot::PlotLine ( "Gyro Z", &_gyroZ[0].x, &_gyroZ[0].y, _gyroZ.size(), 0, 0, sizeof(ImVec2) );
                }
                ImPlot::EndPlot();
            }
            
            static bool AccY_ImAxis_Y2 = false, AccZ_ImAxis_Y3 = false;
            
            ImGui::Checkbox("AccY ImAxis_Y2", &AccY_ImAxis_Y2); ImGui::SameLine();
            ImGui::Checkbox("AccZ ImAxis_Y3", &AccZ_ImAxis_Y3);
            
            if ( ImPlot::BeginPlot("AccPlot", ImVec2(-1,600)) )
            {
                ImPlot::SetupAxes ( "t, ms", "AccX, g", ImPlotAxisFlags_AutoFit, ImPlotAxisFlags_AutoFit );
                ImPlot::SetupAxesLimits(-100, 100, 0, 100000);
                
                if ( AccY_ImAxis_Y2 )
                {
                    ImPlot::SetupAxis ( ImAxis_Y2, "AccY, g", ImPlotAxisFlags_AutoFit | ImPlotAxisFlags_AuxDefault );
                    ImPlot::SetupAxisLimits(ImAxis_Y2, -200, 200);
                }
                
                if ( AccZ_ImAxis_Y3 )
                {
                    ImPlot::SetupAxis ( ImAxis_Y3, "AccZ, g", ImPlotAxisFlags_AutoFit | ImPlotAxisFlags_AuxDefault );
                    ImPlot::SetupAxisLimits(ImAxis_Y3, -200, 200);
                }
                
                ImPlot::SetupAxesLimits(0, 15000, 0, 100000);
                if ( !_accX.empty() && !_accY.empty() && !_accZ.empty() && !visual.empty() )
                {
                    ImPlot::SetAxes(ImAxis_X1, ImAxis_Y1);
                    ImPlot::PlotLine ( "Acc X", &_accX[0].x, &_accX[0].y, _accX.size(), 0, 0, sizeof(ImVec2) );
                    
                    if ( AccY_ImAxis_Y2 )
                        ImPlot::SetAxes(ImAxis_X1, ImAxis_Y2);
                    ImPlot::PlotLine ( "Acc Y", &_accY[0].x, &_accY[0].y, _accY.size(), 0, 0, sizeof(ImVec2) );
                    ImPlot::PlotLine ( "Visual Acc Y", &visual[0].x, &visual[0].y, visual.size(), 0, 0, sizeof(ImVec2) );
                    
                    if ( AccZ_ImAxis_Y3 )
                        ImPlot::SetAxes(ImAxis_X1, ImAxis_Y3);
                    ImPlot::PlotLine ( "Acc Z", &_accZ[0].x, &_accZ[0].y, _accZ.size(), 0, 0, sizeof(ImVec2) );
                }
                ImPlot::EndPlot();
            }
            
//             ImGui::Text("Data accelerometer and gyroscope");
//             static float history = 5000;
//             ImGui::SliderFloat("History",&history, 1, 10000);
//             
//             static ImPlotAxisFlags flagsX = ImPlotAxisFlags_NoTickLabels | ImPlotAxisFlags_AutoFit;
//             static ImPlotAxisFlags flagsY = ImPlotAxisFlags_NoTickLabels;
//             
//             if ( ImPlot::BeginPlot("GyroPlot", ImVec2(-1,200)) )
//             {
//                 ImPlot::SetupAxes(NULL, NULL, flagsX, flagsY);
//                 ImPlot::SetupAxisLimits(ImAxis_X1, t - history, t, ImGuiCond_Always);
//                 ImPlot::SetupAxisLimits(ImAxis_Y1, -1000, 1000);
//                 
//                 if ( !gyroX.Data.empty() && !gyroY.Data.empty() && !gyroZ.Data.empty() )
//                 {
//                     ImPlot::PlotLine("Gyro X", &gyroX.Data[0].x, &gyroX.Data[0].y, gyroX.Data.size(), 0, 0, 2 * sizeof(int16_t));
//                     ImPlot::PlotLine("Gyro Y", &gyroY.Data[0].x, &gyroY.Data[0].y, gyroY.Data.size(), 0, 0, 2 * sizeof(int16_t));
//                     ImPlot::PlotLine("Gyro Z", &gyroZ.Data[0].x, &gyroZ.Data[0].y, gyroZ.Data.size(), 0, 0, 2 * sizeof(int16_t));
//                 }
//                 ImPlot::EndPlot();
//             }
//             
//             if ( ImPlot::BeginPlot("AccPlot", ImVec2(-1,200)) )
//             {
//                 ImPlot::SetupAxes(NULL, NULL, flagsX, flagsY);
//                 ImPlot::SetupAxisLimits(ImAxis_X1, t - history, t, ImGuiCond_Always);
//                 ImPlot::SetupAxisLimits(ImAxis_Y1, -1000, 1000);
//                 
//                 if ( !accX.Data.empty() && !accY.Data.empty() && !accZ.Data.empty() )
//                 {
//                     ImPlot::PlotLine("Acc X", &accX.Data[0].x, &accX.Data[0].y, accX.Data.size(), 0, 0, 2 * sizeof(int16_t));
//                     ImPlot::PlotLine("Acc Y", &accY.Data[0].x, &accY.Data[0].y, accY.Data.size(), 0, 0, 2 * sizeof(int16_t));
//                     ImPlot::PlotLine("Acc Z", &accZ.Data[0].x, &accZ.Data[0].y, accZ.Data.size(), 0, 0, 2 * sizeof(int16_t));
//                 }
//                 ImPlot::EndPlot();
//             }
        
            ImGui::End();
        }
        
        ImGui::Render();
        glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Update and Render additional Platform Windows
        // (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
        //  For this specific demo app we could also call SDL_GL_MakeCurrent(window, gl_context) directly)
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
            SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
        }

        SDL_GL_SwapWindow(window);
    }
}
