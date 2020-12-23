#ifndef __PLAYER__
#define __PLAYER__

#include "entity.hpp"

class Player : 
    public Entity
{
    public:
        Player ( float x, float y, sf::Texture& texture_sheet );
        virtual ~Player ();

        //FUNCTIONS
        virtual void update ( const float& dt );

    private:
        //VARIABLES

        //INITIALIZER FUNCTIONS
        void init_variables( void );
        void init_components ( void );
};

#endif //__PLAYER__