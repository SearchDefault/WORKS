//INCLUDE CALSS
#include "chank.hpp"

Chunk :: Chunk ()
{
    this -> tiles** = new Tile [ CHUNK_SIZE ];

    for ( int i = 0; i < CHUNK_SIZE; i++ )
    {
        this -> *tiles[ i ] = new Tile [ CHUNK_SIZE ];
    }
}