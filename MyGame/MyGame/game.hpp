//SFML LIB
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

//STANDART LIB
#include <string>

//INCLUDE WORLD
#include "world.hpp"

class Game : public sf::Transformable, sf::Drawable
{
    public:
        Game ();
        void Update ();
        void draw ( sf::RenderTarget& target, sf::RenderStates states );

    protected:
        World* world;
};
