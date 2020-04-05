//SFML LIB
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

//INCLUDE CHUNK CLASS
#include "chank.hpp"

//CONST WORLD SIZE
#define WORLD_SIZE 25

class World : public sf::Transformable, sf::Drawable
{
    public:
        World ();
        void draw ( sf::RenderTarget& target, sf::RenderStates states ) const;

        Chunk** chunks;
};