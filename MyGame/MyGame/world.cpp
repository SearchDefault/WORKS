//INCLUDE CLASS
#include "world.hpp"

World :: World ()
{
    this -> chunks** = new Chunk [ WORLD_SIZE ];

    for ( int i = 0; i < CHUNK_SIZE; i++ )
    {
        this -> *chanks[ i ] = new Chunk [ WORLD_SIZE ];
    }
}