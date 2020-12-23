#ifndef __HITBOX_COMPONENT__
#define __HITBOX_COMPONENT__

//INCLUDE STANDART LIB
#include <iostream>
#include <ctime>
#include <cstdlib>

//INCLUDE SFML LIB
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class HitboxComponent
{
    public:
        HitboxComponent ( sf::Sprite& sprite, float offset_x, float offset_y, float width, float height );
        virtual ~HitboxComponent ();

        //FUNCTIONS
        bool check_intersect ( const sf::FloatRect& frect );

        void update ();
        void render ( sf::RenderTarget& target );

    private:
        sf::Sprite& sprite;
        sf::RectangleShape hitbox;
        float offset_x;
        float offset_y;
};

#endif //__HITBOX_COMPONENT__//