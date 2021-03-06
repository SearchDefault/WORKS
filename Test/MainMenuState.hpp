#ifndef __MAIN_MENU_STATE__
#define __MAIN_MENU_STATE__

#include "gamestate.hpp"
#include "EditorState.hpp"
#include "Button.hpp"

class MainMenuState :
    public State
{
    public:
        MainMenuState ( sf::RenderWindow* window, std::map<std::string, int>* supported_keys, std::stack< State* >* states );
        virtual ~MainMenuState ();

        //FUNCTIONS
        void update_input ( const float& dt );
        void update_buttons ( void );
        void update ( const float& dt );
        void render_buttons ( sf::RenderTarget& target );
        void render ( sf::RenderTarget* target = NULL );

    protected:
        //Function
        void init_variables ( void );
        void init_background ( void );
        void init_fonts ( void );
        void init_key_binds ( void );
        void init_buttons ( void );

        //Variables
        sf::Texture background_texture;
        sf::RectangleShape background;
        sf::Font font;

        std::map< std::string, Button* > buttons;
};

#endif //__MAIN_MENU_STATE__