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

    this -> create_hitbox_component ( this -> sprite, 86.f, 74.f, 86.f, 111.f );
    this -> create_movement_component ( 350.f, 15.f, 5.f ); //2.f 0.05f 0.03f
    this -> create_animation_component ( texture_sheet );

    this -> animation_component -> add_animation ( "IDLE", 11.f, 0, 0, 13, 0, 192, 192 );
    this -> animation_component -> add_animation ( "WALK", 7.f, 0, 1, 11, 1, 192, 192 );
    this -> animation_component -> add_animation ( "ATTACK", 6.f, 0, 2, 13, 2, 192*2, 192 );
}

Player::~Player ()
{}

//FUNCTIONS
void Player::update ( const float& dt )
{
    this -> movement_component -> update ( dt );

    if ( this -> movement_component -> get_state( IDLE ) )
    {
        this -> animation_component -> play ( "IDLE", dt );
    }
    else if ( this -> movement_component -> get_state( MOVING_LEFT ) )
    {
        this -> sprite.setOrigin ( 0.f, 0.f );
        this -> sprite.setScale ( 1.f, 1.f );
        this -> animation_component -> play ( "WALK", dt, this -> movement_component -> get_velocity ().x, this -> movement_component -> get_max_velocity () );
    }
    else if ( this -> movement_component -> get_state( MOVING_RIGHT ) )
    {
        this -> sprite.setOrigin ( 258.f, 0.f );
        this -> sprite.setScale ( -1.f, 1.f );
        this -> animation_component -> play ( "WALK", dt, this -> movement_component -> get_velocity ().x, this -> movement_component -> get_max_velocity () );
    }
    else if ( this -> movement_component -> get_state( MOVING_UP ) )
    {
        this -> animation_component -> play ( "WALK", dt, this -> movement_component -> get_velocity ().y, this -> movement_component -> get_max_velocity () );
    }
    else if ( this -> movement_component -> get_state( MOVING_DOWN ) )
    {
        this -> animation_component -> play ( "WALK", dt, this -> movement_component -> get_velocity ().y, this -> movement_component -> get_max_velocity () );
    }

    this -> hitbox_component -> update ();
}