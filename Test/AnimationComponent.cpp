#include "AnimationComponent.hpp"

AnimationComponent::AnimationComponent ( sf::Sprite& sprite, sf::Texture& texture_sheet )
    :   sprite ( sprite ), texture_sheet ( texture_sheet ), last_animation ( NULL )
{}

AnimationComponent::~AnimationComponent ()
{
    for ( auto& i : this -> animations )
    {
        delete i.second;
    }
}

//FUNCTIONS
void AnimationComponent::add_animation ( const std::string key, float animation_timer,
                            int start_frames_x, int start_frames_y, int frames_x, int frames_y, int width, int height )
{
    this -> animations[ key ] = new Animation (
        this -> sprite,
        this -> texture_sheet,
        animation_timer, start_frames_x, start_frames_y,
        frames_x, frames_y,
        width, height
    );
}

void AnimationComponent::play ( const std::string key, const float& dt )
{
    if ( this -> last_animation != this -> animations[key] )
    {
        if ( this -> last_animation == NULL )
            this -> last_animation = this -> animations[key];
        else
        {
            this -> last_animation -> reset();
            this -> last_animation = this -> animations[key];
        }
    }

    this -> animations[ key ] -> play ( dt );
}