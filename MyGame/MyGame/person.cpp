//INCLUDE CLASS
#include "person.hpp"

Person::Person ( RenderWindow* win )
{
    this -> CurrentFrame = 0;//THIS TEST
    this -> win = win;
    this -> texture.loadFromFile ( "Image/person" );

    this -> sprite.setTexture ( this -> texture );
    this -> sprite.setTextureRect ( IntRect ( 0, 0, 1024 / 9, 683 / 6 ) );
    this -> sprite.setOrigin ( Vector2f ( this -> sprite.getTextureRect ().width / 2, this -> sprite.getTextureRect ().height / 2 ) );

    this -> sprite.setPosition ( 1024 / 2, 786 / 2 );
}

void Person::draw ()
{
    this -> win -> draw ( this -> sprite );
}

void Person::update ( float time )
{
    static bool side_mov = false; //false - left; true - right

    if ( Keyboard::isKeyPressed ( Keyboard::Key::W ) )
    {
        this -> sprite.move ( 0, time * -0.2 );
    }
    else if ( Keyboard::isKeyPressed ( Keyboard::Key::S ) )
    {
        this -> sprite.move ( 0, time * 0.2 );
    }
    else if ( Keyboard::isKeyPressed ( Keyboard::Key::A ) )
    {
        side_mov = false;

        this -> CurrentFrame += time * 0.005;

        if ( this -> CurrentFrame > 3 )
            this -> CurrentFrame -= 3;

        this -> sprite.setTextureRect ( IntRect ( ( 1024 / 9 ) * ( int ( this -> CurrentFrame ) + 7 ), 0, -( 1024 / 9 ), 683 / 6 ) );
        this -> sprite.move ( time * -0.2, 0 );
    }
    else if ( Keyboard::isKeyPressed ( Keyboard::Key::D ) )
    {
        side_mov = true;

        this -> CurrentFrame += time * 0.005;

        if ( this -> CurrentFrame > 3 )
            this -> CurrentFrame -= 3;

        this -> sprite.setTextureRect ( IntRect ( ( 1024 / 9 ) * ( int ( this -> CurrentFrame ) + 6 ), 0, ( 1024 / 9 ), 683 / 6 ) );
        this -> sprite.move ( time * 0.2, 0 );
    }
    else if ( !side_mov )
        this -> sprite.setTextureRect ( IntRect ( 0, 0, 1024 / 9, 683 / 6 ) );
    else
        this -> sprite.setTextureRect ( IntRect ( 1024 / 9, 0, -1024 / 9, 683 / 6 ) );
}