#include "gamestate.hpp"

void GameState::init_key_binds ( void )
{
    std::ifstream ifs ( "Config/gamestate_keybinds.ini" );

    if ( ifs.is_open () )
    {
        std::string key;
        std::string key_2;

        while ( ifs >> key >> key_2 )
            this -> key_binds[ key ] = this -> supported_keys -> at( key_2 );
    }

    ifs.close ();
}

void GameState::init_textures ( void )
{
    if ( !this -> textures[ "PLAYER_SHEET" ].loadFromFile ( "Resourses/Images/Sprites/Player/PLAYER_SHEET.png" ) )
    {
        throw "ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER_TEXTURE" ;
    }
}

void GameState::init_players ( void )
{
    this -> player = new Player ( 0, 0, this -> textures["PLAYER_SHEET"] );
}

GameState::GameState ( sf::RenderWindow* window, std::map<std::string, int>* supported_keys, std::stack< State* >* states )
    : State ( window, supported_keys, states )
{
    this -> init_key_binds ();
    this -> init_textures ();
    this -> init_players ();
}

GameState::~GameState ( void )
{
    delete this -> player;
}

//FUNCTIONS
void GameState::update_input ( const float& dt )
{
    //Update player input
    if ( sf::Keyboard::isKeyPressed ( sf::Keyboard::Key ( this -> key_binds.at ( "MOVE_LEFT" ) ) ) )
        this -> player -> move ( -1.f, 0.f, dt );
    if ( sf::Keyboard::isKeyPressed ( sf::Keyboard::Key ( this -> key_binds.at ( "MOVE_RIGHT" ) ) ) )
        this -> player -> move ( 1.f, 0.f, dt );
    if ( sf::Keyboard::isKeyPressed ( sf::Keyboard::Key ( this -> key_binds.at ( "MOVE_UP" ) ) ) )
        this -> player -> move ( 0.f, -1.f, dt );
    if ( sf::Keyboard::isKeyPressed ( sf::Keyboard::Key ( this -> key_binds.at ( "MOVE_DOWN" ) ) ) )
        this -> player -> move ( 0.f, 1.f, dt );

    if ( sf::Keyboard::isKeyPressed ( sf::Keyboard::Key ( this -> key_binds.at ( "CLOSE" ) ) ) )
        this -> end_state();
}

void GameState::update ( const float& dt )
{
    this -> update_mouse_positions ();
    this -> update_input ( dt );

    this -> player -> update ( dt );
}

void GameState::render ( sf::RenderTarget* target )
{
    if ( !target )
        target = this -> window;

    this -> player -> render ( *target );
}