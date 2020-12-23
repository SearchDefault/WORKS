#include "Player.hpp"

//INITIALIZER FUNCTIONS
void Player::init_variables ()
{}

void Player::init_components ()
{

}

//CONSTRUCTORS //DESTRUCTORS
Player::Player ( float x, float y, sf::Texture& texture_sheet )
{
    this -> init_variables ();

    this -> set_position ( x, y );

    this -> create_hitbox_component ( this -> sprite, 86.f, 81.f, 86.f, 111.f );
    this -> create_movement_component ( 2.f, 0.05f, 0.03f ); //1.f 0.05f 0.03f
    this -> create_animation_component ( texture_sheet );

    this -> animation_component -> add_animation ( "IDLE_LEFT", 10.f, 0, 0, 13, 0, 192, 192 );
    this -> animation_component -> add_animation ( "WALK_LEFT", 10.f, 0, 1, 11, 1, 192, 192 );
}

Player::~Player ()
{}

//FUNCTIONS
void Player::update ( const float& dt )
{
    this -> movement_component -> update ( dt );

    if ( this -> movement_component -> get_state( IDLE ) )
        this -> animation_component -> play ( "IDLE_LEFT", dt );

    else if ( this -> movement_component -> get_state( MOVING_LEFT ) )
    {
        this -> sprite.setScale ( 1.f, 1.f );
        this -> animation_component -> play ( "WALK_LEFT", dt );
    }
    else if ( this -> movement_component -> get_state( MOVING_RIGHT ) )
    {
        this -> sprite.setOrigin ( 258.f, 0.f );
        this -> sprite.setScale ( -1.f, 1.f );
        this -> animation_component -> play ( "WALK_LEFT", dt );
    }

    this -> hitbox_component -> update ();
}