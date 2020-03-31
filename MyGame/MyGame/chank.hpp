//SFML LIB
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

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