#ifndef __GAME_HPP__
#define __GAME_HPP__

//INCLUDE STATE CLASS//
#include "MainMenuState.hpp"

class Game
{
    public:
        //CONSTRUCTOR AND DESTRUCTOR
        Game ( void );
        virtual ~Game ( void );

        //FUNCTIONS

        //Regular
        void end_application ( void );

        //Update
        void update_sf_events ( void );
        void update_dt ( void );
        void update ( void );

        //Render
        void render ( void );

        //Core
        void run ( void );

    protected:
        //Variables
        sf::RenderWindow* window;
        sf::Event sfEvent;
        std::vector< sf::VideoMode > video_modes;
        sf::ContextSettings window_settings;

        bool fullscreen;

        sf::Clock dtClock;
        float dt;

        std::stack<State*> states;
        std::map<std::string, int> supported_keys;

        //Initializations
        void init_variables ( void );
        void init_window ( void );
        void init_keys ( void );
        void init_states ( void );
};

#endif //__GAME_HPP__