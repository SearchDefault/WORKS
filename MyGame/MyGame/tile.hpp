//SFML LIB
#include <SFML/Graphics.hpp>

//STANDART LIB
#include <string>

enum TileType
{
    NONE,
    GROUNG
};

class Tile
{
    public:
        Tile ();

    protected:
        TileType* type = TileType::NONE;
};