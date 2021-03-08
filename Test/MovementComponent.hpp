#ifndef __MOVEMENT_COMPONENT__
#define __MOVEMENT_COMPONENT__

//INCLUDE STANDART LIB
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <ctime>
#include <vector>
#include <stack>
#include <map>

//INCLUDE SFML LIB
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

enum movement_states
{
    IDLE = 0,
    MOVING,
    MOVING_LEFT,
    MOVING_RIGHT,
    MOVING_UP,
    MOVING_DOWN
};

class MovementComponent
{
    public:
        //CONSTURCTOR//DESTRUCTOR
        MovementComponent ( sf::Sprite& sprite, float max_velocity, float acceleration, float deceleration );
        virtual ~MovementComponent ();

        //ACCESSORS
        const float& get_max_velocity() const;
        const sf::Vector2f& get_velocity() const;
        
        //FUNCTIONS
        const bool get_state ( const short unsigned state ) const;

        void move ( const float x, const float y, const float& dt );
        void update ( const float& dt );

    private:
        sf::Sprite& sprite;

        sf::Vector2f velocity;

        float max_velocity;
        float acceleration;
        float deceleration;

        //INITIALIZER FUNCTIONS
};

#endif //__MOVEMENT_COMPONENT__