#include "entity.hpp"

void Entity::init_variables ( void )
{
    this -> hitbox_component = NULL;
    this -> movement_component = NULL;
    this -> animation_component = NULL;
}

Entity::Entity ( void )
{
    this -> init_variables();
}

Entity::~Entity ( void )
{
    delete this -> hitbox_component;
    delete this -> movement_component;
    delete this -> animation_component;
}

//COMPONENT FUNTIONS
void Entity::set_texture ( sf::Texture& texture )
{
    this -> sprite.setTexture ( texture );
}

void Entity::create_hitbox_component ( sf::Sprite& sprite, float offset_x, float offset_y, float width, float height )
{
    this -> hitbox_component = new HitboxComponent ( sprite, offset_x, offset_y, width, height );
}

void Entity::create_movement_component ( const float max_velocity, const float acceleration, const float deceleration )
{
    this -> movement_component = new MovementComponent ( this -> sprite, max_velocity, acceleration, deceleration );
}

void Entity::create_animation_component ( sf::Texture& texture_sheet )
{
    this -> animation_component = new AnimationComponent ( this -> sprite, texture_sheet );
}

//FUNCTIONS
void Entity::set_position ( const float x, const float y )
{
        this -> sprite.setPosition ( x, y );
}

void Entity::move ( const float dir_x, const float dir_y, const float& dt )
{
    if ( this -> movement_component )
    {
        this -> movement_component -> move ( dir_x, dir_y, dt ); //sets velocity
    }
}

void Entity::update ( const float& dt )
{}

void Entity::render ( sf::RenderTarget& target )
{
    target.draw ( this -> sprite );

    if ( this -> hitbox_component )
        this -> hitbox_component -> render ( target );
}