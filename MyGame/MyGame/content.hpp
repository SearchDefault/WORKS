//INCLUDE SFML
#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;

class Content
{
    public:
        static void Load ();

    protected:
        static Texture texTile0;
        const String CONTENT_DIR = "..\\Content\\";
};