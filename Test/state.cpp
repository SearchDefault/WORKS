#include "state.hpp"

State::State ( sf::RenderWindow* window, std::map<std::string, int>* supported_keys, std::stack< State* >* states )
{
    this -> window = window;
    this -> supported_keys = supported_keys;
    this -> states = states;
    this -> quit = false;
}

State::~State ( void )
{}

const bool& State::get_quit ( void ) const
{
    return this -> quit;
}

void State::end_state ( void )
{
    this -> quit = true;
}   

void State::update_mouse_positions ( void )
{
    this -> mouse_pos_screen = sf::Mouse::getPosition ();
    this -> mouse_pos_window = sf::Mouse::getPosition ( *this -> window );
    this -> mouse_pos_view = this -> window -> mapPixelToCoords ( sf::Mouse::getPosition ( *this -> window ) );
}