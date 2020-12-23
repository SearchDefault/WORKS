#include "MovementComponent.hpp"

//CONSTRUTOR//DESTRUCTOR
MovementComponent::MovementComponent ( sf::Sprite& sprite, float max_velocity, float acceleration, float deceleration )
    : sprite ( sprite ), max_velocity ( max_velocity ), acceleration ( acceleration ), deceleration ( deceleration )
{
    this -> max_velocity = max_velocity;
}

MovementComponent::~MovementComponent ()
{}

//ACCESSORS
const sf::Vector2f & MovementComponent::get_velocity() const
{
    return this -> velocity;
}

//FUNCTIONS
const bool MovementComponent::get_state ( const short unsigned state ) const
{
    switch ( state )
    {
        case IDLE:

            if ( this -> velocity.x == 0.f && this -> velocity.y == 0.f )
                return true;

            return false;

            break;

        case MOVING:

            if ( this -> velocity.x != 0.f || this -> velocity.y != 0.f )
                return true;

            break;

        case MOVING_LEFT:

            if ( this -> velocity.x < 0.f)
                return true;

            break;

        case MOVING_RIGHT:

            if ( this -> velocity.x > 0.f)
                return true;

            break;

        case MOVING_UP:

            if ( this -> velocity.y < 0.f)
                return true;

            break;

        case MOVING_DOWN:

            if ( this -> velocity.y > 0.f)
                return true;

            break;
    }

    return false;
}

void MovementComponent::move ( const float dir_x, const float dir_y, const float& dt )
{
    /* ACCELERATION A SPRITE UNTIL IF REACHES THE MAX VELOCITY */

    this -> velocity.x += this -> acceleration * dir_x;
    this -> velocity.y += this -> acceleration * dir_y;
}

void MovementComponent::update ( const float& dt )
{
    /*
        DESELERATES THE SPRITE AND CONTROLS THE MAXIMUM VELOCITY.
        MOVES THE SPRITE.
    */

    if ( this -> velocity.x > 0.f ) //Check for positive x
    {
        //Max velocity check
        if ( this -> velocity.x > this -> max_velocity )
            this -> velocity.x = this -> max_velocity;

        //Deceleration
        this -> velocity.x -= deceleration;
        if ( this -> velocity.x < 0.f )
            this -> velocity.x = 0.f;
    }
    else if ( this -> velocity.x < 0.f ) //Check for negative x
    {
        //Max velocity check
        if ( this -> velocity.x < -this -> max_velocity )
            this -> velocity.x = -this -> max_velocity;

        //Deceleration
        this -> velocity.x += deceleration;
        if ( this -> velocity.x > 0.f )
            this -> velocity.x = 0.f;
    }

    if ( this -> velocity.y > 0.f ) //Check for positive y
    {
        //Max velocity check
        if ( this -> velocity.y > this -> max_velocity )
            this -> velocity.y = this -> max_velocity;

        //Deceleration
        this -> velocity.y -= deceleration;
        if ( this -> velocity.y < 0.f )
            this -> velocity.y = 0.f;
    }
    else if ( this -> velocity.y < 0.f ) //Check for negative y
    {
        //Max velocity check
        if ( this -> velocity.y < -this -> max_velocity )
            this -> velocity.y = -this -> max_velocity;

        //Deceleration
        this -> velocity.y += deceleration;
        if ( this -> velocity.y > 0.f )
            this -> velocity.y = 0.f;
    }

    //FINAL MOVE
    this -> sprite.move ( this -> velocity ); //*dt
}