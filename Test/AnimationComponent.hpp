#ifndef __ANIMATION_COMPONENT__
#define __ANIMATION_COMPONENT__

#include <iostream>
#include <string>
#include <map>

//INCLUDE SFML LIB
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class AnimationComponent
{
    public:
        AnimationComponent ( sf::Sprite& sprite, sf::Texture& texture_sheet );
        virtual ~AnimationComponent ();

        //FUNCTIONS
        void add_animation ( const std::string key, float animation_timer,
                            int start_frames_x, int start_frames_y, int frames_x, int frames_y, int width, int height );

        void play ( const std::string key, const float& dt );

    private:
        class Animation
        {
            public:
                //VARIABLES
                sf::Sprite& sprite;
                sf::Texture& texture_sheet;
                float animation_timer;
                float timer;
                int width;
                int height;
                sf::IntRect start_rect;
                sf::IntRect current_rect;
                sf::IntRect end_rect;

                Animation ( sf::Sprite& sprite, sf::Texture& texture_sheet, float animation_timer,
                            int start_frames_x, int start_frames_y, int frames_x, int frames_y, int width, int height )
                    :   sprite ( sprite ), texture_sheet ( texture_sheet ), animation_timer ( animation_timer ),
                         width ( width ), height ( height )
                {
                    this -> timer = 0.f;
                    this -> start_rect = sf::IntRect ( start_frames_x * width, start_frames_y * height, width, height );
                    this -> current_rect = this -> start_rect;
                    this -> end_rect = sf::IntRect ( frames_x * width, frames_y * height, width, height );
                
                    this -> sprite.setTexture ( texture_sheet, true );
                    this -> sprite.setTextureRect ( this -> start_rect );
                }

                //FUNCTIONS
                void play ( const float& dt )
                {
                    //UPDATE TIMER
                    this -> timer += 1.f;

                    if ( this -> timer >= this -> animation_timer )
                    {
                        //RESET TIMER
                        this -> timer = 0.f;

                        //ANIMATE
                        if ( this -> current_rect != this -> end_rect )
                        {
                            this -> current_rect.left += this -> width;
                        }
                        else    //RESET
                        {
                            this -> current_rect.left = this -> start_rect.left;
                        }

                        this -> sprite.setTextureRect ( this -> current_rect );
                    }
                }
                
                void reset ()
                {
                    this -> timer = 0.f;
                    this -> current_rect = this -> start_rect;
                }
        };

        sf::Sprite& sprite;
        sf::Texture& texture_sheet;
        std::map<std::string, Animation*> animations;
        Animation* last_animation;
};

#endif // __ANIMATION_COMPONENT__ //