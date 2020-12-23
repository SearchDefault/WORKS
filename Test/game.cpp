#include "game.hpp"

//INIT
void Game::init_variables ( void )
{
    this -> window = NULL;
    this -> fullscreen = false;
    this -> dt = 0.f;
}

void Game::init_window ( void )
{
    //VARIABLES FROM WINDOW CONFIGURATION//
    this -> video_modes = sf::VideoMode::getFullscreenModes ();

    std::string title = "NONE";
    sf::VideoMode window_bounds = sf::VideoMode::getDesktopMode ();
    this -> fullscreen = false;
    unsigned frame_limit = 120;
    bool vertical_synk = false;
    unsigned antialiasing_level = 0;

    //FILE OPEN//
    std::fstream file ( "Config/window.ini" );
    //READ FROM FILE//
    if ( file.is_open () )
    {
        std::getline ( file, title );
        file >> window_bounds.width >> window_bounds.height;
        file >> this -> fullscreen;
        file >> frame_limit;
        file >> vertical_synk;
        file >> antialiasing_level;
    }
    file.close ();

    this -> window_settings.antialiasingLevel = antialiasing_level;

    if ( this -> fullscreen )
        this -> window = new sf::RenderWindow ( window_bounds, title, sf::Style::Fullscreen, window_settings );
    else
        this -> window = new sf::RenderWindow ( window_bounds, title, sf::Style::Titlebar | sf::Style::Close, window_settings );
    
    this -> window -> setFramerateLimit ( frame_limit );
    this -> window -> setVerticalSyncEnabled ( vertical_synk );
}

void Game::init_keys ( void )
{
    std::ifstream ifs ( "Config/supported_keys.ini" );

    if ( ifs.is_open () )
    {
        std::string key;
        int key_value;

        while ( ifs >> key >> key_value )
            this -> supported_keys[ key ] = key_value;
    }

    ifs.close ();

    //SOME BUGS
    for ( auto item : this -> supported_keys )
    {
        std::cout << item.first << ' ' << item.second << std::endl;
    }
}

void Game::init_states ( void )
{
    this -> states.push ( new MainMenuState ( this -> window, &this -> supported_keys, &this -> states ) );
}

//CONSTRUCTOR AND DESTRUCTOR
Game::Game ( void )
{
    this -> init_window ();
    this -> init_keys ();
    this -> init_states ();
}

Game::~Game ( void )
{
    delete this -> window;

    while ( !this -> states.empty () )
    {
        delete this -> states.top ();
        this -> states.pop ();
    }
}

//FUNCTIONS
void Game::end_application ( void )
{
    std::cout << "Ending Application..." << std::endl;
}

void Game::update_sf_events ( void )
{
    while ( this -> window -> pollEvent ( this -> sfEvent ) )
    {
        if ( this -> sfEvent.type == sf::Event::Closed )
            this -> window -> close ();
    }
}

void Game::update_dt ()
{
    this -> dt = this -> dtClock.getElapsedTime().asSeconds();
}

void Game::update ( void )
{
    this -> update_sf_events ();

    if ( !this -> states.empty () )
    {
        this -> states.top () -> update ( this -> dt );
    
        if ( this -> states.top () -> get_quit () )
        {
            this -> states.top () -> end_state ();
            delete this -> states.top ();
            this -> states.pop ();
        }
    }
    //Aplication end
    else
    {
        this -> end_application ();
        this -> window -> close ();
    }
}

void Game::render ( void )
{
    this -> window -> clear ();

    //render items
    if ( !this -> states.empty () )
        this -> states.top () -> render ();

    this -> window -> display ();
}

void Game::run ( void )
{
    while ( this -> window -> isOpen () )
    {
        this -> update_dt ();
        this -> update ();
        this -> render ();
    }
}