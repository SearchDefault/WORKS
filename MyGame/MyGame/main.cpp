//INCLUDE STANDART LIBS
#include <iostream>
#include <string>

//INCLUDE SFML LIBS
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

//INCLUDE CLASSES
#include "content.hpp"
#include "game.hpp"
#include "person.hpp"

int
main ( int argv, char** argc )
{
    //GAME WINDOW
    sf::RenderWindow win ( sf::VideoMode ( 1024, 786 ), "END STATION" );

    //TIME
    sf::Clock clock;
    float time;
    win.setVerticalSyncEnabled ( true );

    //CONTENT
    Content* content;
    content -> Load ();

    //GAME
    static Game* game;

    //NEW PLAYER
    //Person player ( &win );

    //LOOP BEFORE WINDOW IS CLOSED
    while ( win.isOpen () )
    {
        time = clock.getElapsedTime ().asMilliseconds ();
        clock.restart ();
        game = new Game ();

        sf::Event event;

        //EVENT LOOP
        while ( win.pollEvent ( event ) )
        {
            if ( event.type == sf::Event::Closed || ( event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape ) )
                win.close ();
        }

        game.Update ();

        win.clear ();

        game -> Draw ( &win );

        //player.update ( time );
        //player.draw ();

        win.display ();
    }

    return 0;
}