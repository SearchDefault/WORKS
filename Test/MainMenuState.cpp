#include "MainMenuState.hpp"

//Init functions
void MainMenuState::init_variables ( void )
{

}

void MainMenuState::init_background ( void )
{
    this -> background.setSize
    (
        sf::Vector2f
        (
            static_cast<float> ( this -> window -> getSize ().x ),
            static_cast<float> ( this -> window -> getSize ().y )
        )
    );

    if ( !this -> background_texture.loadFromFile ( "Resourses/Images/Backgrounds/bg1.png" ) )
    {
        throw ( "ERROR::MAIN_MENU_STATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE" );
    }

    this -> background.setTexture ( &this -> background_texture );
}

void MainMenuState::init_fonts ( void )
{
    if ( !this -> font.loadFromFile ( "Fonts/Dosis-Light.ttf" ) )
        throw ( "ERROR::MAIN_MENU_STATE::COULD_NOT_LOAD_FONT" );
}

void MainMenuState::init_key_binds ( void )
{
    std::ifstream ifs ( "Config/mainmenustate_keybinds.ini" );

    if ( ifs.is_open () )
    {
        std::string key;
        std::string key_2;

        while ( ifs >> key >> key_2 )
            this -> key_binds[ key ] = this -> supported_keys -> at( key_2 );
    }

    ifs.close ();
}

void MainMenuState::init_buttons ( void )
{
    this -> buttons[ "GAME_STATE" ] = new Button ( 300.f, 480.f, 250.f, 50.f,
        &this -> font, "New Game", 50,
        sf::Color ( 70, 70, 70, 200 ), sf::Color ( 150, 150, 150, 250 ), sf::Color ( 20, 20, 20, 50 ),
        sf::Color ( 70, 70, 70, 0 ), sf::Color ( 150, 150, 150, 0 ), sf::Color ( 20, 20, 20, 0 )
    );

    this -> buttons[ "SETTINGS" ] = new Button ( 300, 580, 250, 50,
        &this -> font, "Settings", 50,
        sf::Color ( 70, 70, 70, 200 ), sf::Color ( 150, 150, 150, 250 ), sf::Color ( 20, 20, 20, 50 ),
        sf::Color ( 70, 70, 70, 0 ), sf::Color ( 150, 150, 150, 0 ), sf::Color ( 20, 20, 20, 0 )
    );

    this -> buttons[ "EDITOR_STATE" ] = new Button ( 300, 680, 250, 50,
        &this -> font, "Editor", 50,
        sf::Color ( 70, 70, 70, 200 ), sf::Color ( 150, 150, 150, 250 ), sf::Color ( 20, 20, 20, 50 ),
        sf::Color ( 70, 70, 70, 0 ), sf::Color ( 150, 150, 150, 0 ), sf::Color ( 20, 20, 20, 0 )
    );

    this -> buttons[ "EXIT_STATE" ] = new Button ( 300, 880, 250, 50,
        &this -> font, "Quit", 50,
        sf::Color ( 70, 70, 70, 200 ), sf::Color ( 150, 150, 150, 250 ), sf::Color ( 20, 20, 20, 50 ),
        sf::Color ( 100, 100, 100, 0 ), sf::Color ( 150, 150, 150, 0 ), sf::Color ( 20, 20, 20, 0 )
    );
}

MainMenuState::MainMenuState ( sf::RenderWindow* window, std::map<std::string, int>* supported_keys, std::stack< State* >* states )
    : State ( window, supported_keys, states )
{
    this -> init_variables ();
    this -> init_background ();
    this -> init_fonts ();
    this -> init_key_binds ();
    this -> init_buttons ();
}

MainMenuState::~MainMenuState ( void )
{
    for ( auto& item : this -> buttons )
    {
        delete item.second;
    }
}

//FUNCTIONS
void MainMenuState::update_input ( const float& dt )
{
    //Update player input
}

void MainMenuState::update_buttons ( void )
{
    //Updates all the buttons in the state and handles their functionality//
    for ( auto& item : this -> buttons )
    {
        item.second -> update ( this -> mouse_pos_view );
    }

    //New game
    if ( this -> buttons[ "GAME_STATE" ] -> is_pressed () )
        this -> states -> push ( new GameState ( this -> window, this -> supported_keys, this -> states ) );

    //Settings

    //Editor
    if ( this -> buttons[ "EDITOR_STATE" ] -> is_pressed () )
        this -> states -> push ( new EditorState ( this -> window, this -> supported_keys, this -> states ) );

    //Quit the game
    if ( this -> buttons[ "EXIT_STATE" ] -> is_pressed () )
        this -> end_state();
}

void MainMenuState::update ( const float& dt )
{
    this -> update_mouse_positions ();
    this -> update_input ( dt );

    this -> update_buttons ();
}

void MainMenuState::render_buttons ( sf::RenderTarget& target )
{
    for ( auto& item : this -> buttons )
    {
        item.second -> render ( target );
    }
}

void MainMenuState::render ( sf::RenderTarget* target )
{
    if ( !target )
        target = this -> window;

    target -> draw ( this -> background );

    this -> render_buttons ( *target );

    //REMOVE LATER!!//
    /*sf::Text mouseText;
    mouseText.setPosition ( this -> mouse_pos_view.x, this -> mouse_pos_view.y - 50 );
    mouseText.setFont ( this -> font );
    mouseText.setCharacterSize ( 12 );
    std::stringstream ss;
    ss << this -> mouse_pos_view.x << " " << this -> mouse_pos_view.y;
    mouseText.setString ( ss.str() );

    target -> draw ( mouseText );*/
}