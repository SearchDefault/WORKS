#ifndef __ENTITY_HPP__
#define __ENTITY_HPP__

#include "HitboxComponent.hpp"
#include "MovementComponent.hpp"
#include "AnimationComponent.hpp"

class Entity
{
    public:
        Entity ( void );
        ~Entity ( void );

        //COMPONENT FUNTIONS
        void set_texture ( sf::Texture& texture );
        void create_hitbox_component ( sf::Sprite& sprite, float offset_x, float offset_y, float width, float height );
        void create_movement_component ( const float max_velocity, const float acceleration, const float deceleration );
        void create_animation_component ( sf::Texture& texture_sheet );

        //Functions
        virtual void set_position ( const float x, const float y );
        virtual void move ( const float x, const float y, const float& dt );

        virtual void update ( const float& dt );
        virtual void render ( sf::RenderTarget& target );

    protected:
        sf::Sprite sprite;

        HitboxComponent* hitbox_component;
        MovementComponent* movement_component;
        AnimationComponent* animation_component;

    private:
        void init_variables ( void );
};

#endif //__ENTITY_HPP__