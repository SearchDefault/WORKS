//SFML LIB
#include <SFML/Graphics.hpp>

//STANDART LIB
#include <string>

//INCLUDE WORLD
#include "world.hpp"

class Game
{
    public:
        Game ();
        void Update ();
        void Draw ();

    protected:
        World* world;
};
