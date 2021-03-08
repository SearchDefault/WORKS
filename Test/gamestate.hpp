#ifndef __GAME_STATE_HPP__
#define __GAME_STATE_HPP__

#include "state.hpp"

class GameState : public State
{
    public:
        GameState ( sf::RenderWindow* window, std::map<std::string, int>* supported_keys, std::stack< State* >* states );
        virtual ~GameState ( void );

        //FUNCTIONS
        void update_input ( const float& dt );
        void update ( const float& dt );
        void render ( sf::RenderTarget* target = NULL );

    protected:
        Player* player;

        //Function
        void init_key_binds ( void );
        void init_textures ( void );
        void init_players ( void );
};

#endif //__GAME_STATE_HPP__