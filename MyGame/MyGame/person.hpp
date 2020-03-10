//SFML LIB
#include <SFML/Graphics.hpp>
using namespace sf;

//PERSON CLASS
class Person
{
    public:
        Person ( RenderWindow* win );
        void update ( float time );
        void draw ();

    protected:
        RenderWindow* win;
        Texture texture;
        Sprite sprite;
        Vector2f position;
        float CurrentFrame;
};