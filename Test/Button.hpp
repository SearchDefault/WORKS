#ifndef __BUTTON__
#define __BUTTON__

//INCLUDE STANDART LIB
#include <iostream>
#include <sstream>
#include <ctime>
#include <cstdlib>

//INCLUDE SFML LIB
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

enum Button_States {
    BTN_IDLE,
    BTN_HOVER,
    BTN_ACTIVE
};

class Button
{
    public:
        Button ( float x, float y, float width, float height,
            sf::Font* font, std::string text, unsigned character_size,
            sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
            sf::Color idle_color, sf::Color hover_color, sf::Color active_color );
        ~Button ( void );

        //Accessors
        const bool is_pressed ( void ) const;

        //Functions
        void update ( const sf::Vector2f mouse_pos );
        void render ( sf::RenderTarget& target );

    protected:
        short unsigned Button_States;

        sf::RectangleShape shape;
        sf::Font* font;
        sf::Text text;

        sf::Color text_idle_color;
        sf::Color text_hover_color;
        sf::Color text_active_color;

        sf::Color idle_color;
        sf::Color hover_color;
        sf::Color active_color;
};

#endif //__BUTTON__