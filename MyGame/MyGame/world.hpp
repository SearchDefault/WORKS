//SFML LIB
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

//STANDART LIB
#include <string>

//INCLUDE CHUNK CLASS
#include "chank.hpp"

//CONST WORLD SIZE
#define WORLD_SIZE 25

class World : public sf::Transformable, sf::Drawable
{
    public:
        World ();

    protected:
        Chunk** chunks;
};