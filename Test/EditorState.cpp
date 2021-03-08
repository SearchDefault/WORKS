#include "EditorState.hpp"

//Init functions
void EditorState::init_variables ( void )
{

}

void EditorState::init_background ( void )
{

}

void EditorState::init_fonts ( void )
{
    if ( !this -> font.loadFromFile ( "Fonts/Dosis-Light.ttf" ) )
        throw ( "ERROR::EDITOR_STATE::COULD_NOT_LOAD_FONT" );
}

void EditorState::init_key_binds ( void )
{
    std::ifstream ifs ( "Config/editorstate_keybinds.ini" );

    if ( ifs.is_open () )
    {
        std::string key;
        std::string key_2;

        while ( ifs >> key >> key_2 )
            this -> key_binds[ key ] = this -> supported_keys -> at( key_2 );
    }

    ifs.close ();
}

void EditorState::init_buttons ( void )
{
}

EditorState::EditorState ( sf::RenderWindow* window, std::map<std::string, int>* supported_keys, std::stack< State* >* states )
    : State ( window, supported_keys, states )
{
    this -> init_variables ();
    this -> init_background ();
    this -> init_fonts ();
    this -> init_key_binds ();
    this -> init_buttons ();
}

EditorState::~EditorState ( void )
{
    for ( auto& item : this -> buttons )
    {
        delete item.second;
    }
}

//FUNCTIONS
void EditorState::update_input ( const float& dt )
{
    if ( sf::Keyboard::isKeyPressed ( sf::Keyboard::Key ( this -> key_binds.at ( "CLOSE" ) ) ) )
        this -> end_state();
}

void EditorState::update_buttons ( void )
{
    //Updates all the buttons in the state and handles their functionality//
    for ( auto& item : this -> buttons )
    {
        item.second -> update ( this -> mouse_pos_view );
    }
}

void EditorState::update ( const float& dt )
{
    this -> update_mouse_positions ();
    this -> update_input ( dt );

    this -> update_buttons ();
}

void EditorState::render_buttons ( sf::RenderTarget& target )
{
    for ( auto& item : this -> buttons )
    {
        item.second -> render ( target );
    }
}

void EditorState::render ( sf::RenderTarget* target )
{
    if ( !target )
        target = this -> window;

    this -> render_buttons ( *target );
}