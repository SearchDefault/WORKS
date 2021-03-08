#ifndef __STATE_HPP__
#define __STATE_HPP__

#include "Player.hpp"

class State
{
    public:
        State ( sf::RenderWindow* window, std::map<std::string, int>* suported_keys, std::stack< State* >* states );
        virtual ~State ( void );

        const bool& get_quit ( void ) const;
        
        void end_state ( void );
        
        virtual void update_mouse_positions ( void );
        virtual void update_input ( const float& dt ) = 0;
        virtual void update ( const float& dt ) = 0;
        virtual void render ( sf::RenderTarget* target = NULL ) = 0;

    protected:
        std::stack< State* >* states;
        sf::RenderWindow* window;
        std::map<std::string, int>* supported_keys;
        std::map<std::string, int> key_binds;
        bool quit;

        sf::Vector2i mouse_pos_screen;
        sf::Vector2i mouse_pos_window;
        sf::Vector2f mouse_pos_view;

        //Resources
        std::map<std::string, sf::Texture> textures;

        //Functions
        virtual void init_key_binds ( void ) = 0;
};

#endif //__STATE_HPP__