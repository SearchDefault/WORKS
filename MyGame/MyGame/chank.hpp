//SFML LIB
#include <SFML/Graphics.hpp>

//STANDART LIB
#include <string>

//INCLUDE TILE
#include "tile.hpp"

//CONST CHUNK SIZE
#define CHUNK_SIZE 25

class Chunk
{
    public:
        Chunk ();

    protected:
        Tile** tiles;
};