//INCLUDE CALSS
#include "game.hpp"

Game :: Game ()
{
    this -> world = new World;
}

void Game :: Update ()
{

}

virtual void Game::draw ( sf::RenderTarget target, sf::RenderStates states ) const
{
    for ( int i = 0; i < WORLD_SIZE; i++ )
    {
        for ( int j = 0; j < WORLD_SIZE; j++ )
        {
            target.draw ( chunks[i][j] );
        }
    }
}