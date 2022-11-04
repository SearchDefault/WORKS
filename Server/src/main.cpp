#include <iostream>

#include "./Renderer/Renderer.hpp"

int main ( int argv, char** argc )
{
    // Создание экземпляра окна
    Renderer::WindowContext window;

    // Our state
    bool show_demo_window = false;
    bool show_plot_window = false;
    bool show_logger = false;
    bool show_data_plot = false;

    // Main loop
    bool done = false;
    while (!done)
    {
        window.Update ( done );
        window.Render ( done, show_plot_window, show_demo_window, show_logger, show_data_plot );
    }

    return EXIT_SUCCESS;
}
