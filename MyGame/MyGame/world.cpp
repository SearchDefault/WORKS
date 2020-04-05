//INCLUDE CLASS
#include "world.hpp"

World :: World ()
{
    this -> **chunks = new Chunk [ WORLD_SIZE ];

    for ( int i = 0; i < CHUNK_SIZE; i++ )
    {
        this -> *chanks[ i ] = new Chunk [ WORLD_SIZE ];
    }
}

void Game::draw ( sf::RenderTarget& target, sf::RenderStates states ) const
{
    for ( int i = 0; i < WORLD_SIZE; i++ )
    {
        for ( int j = 0; j < WORLD_SIZE; j++ )
        {
            target.draw ( Chunk::tiles[i][j], states );
        }
    }
}