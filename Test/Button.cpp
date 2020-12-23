#include "Button.hpp"

Button::Button ( float x, float y, float width, float height,
            sf::Font* font, std::string text, unsigned character_size,
            sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
            sf::Color idle_color, sf::Color hover_color, sf::Color active_color )
{
    this -> Button_States = BTN_IDLE;

    this -> shape.setPosition ( sf::Vector2f ( x, y ) );
    this -> shape.setSize ( sf::Vector2f ( width, height ) );
    this -> shape.setFillColor ( idle_color );

    this -> font = font;
    this -> text.setFont ( *this -> font );
    this -> text.setString ( text );
    this -> text.setFillColor ( text_idle_color );
    this -> text.setCharacterSize ( character_size );
    this -> text.setPosition (
        this -> shape.getPosition ().x + ( this -> shape.getGlobalBounds ().width / 2.f ) - this -> text.getGlobalBounds ().width / 2.f,
        this -> shape.getPosition ().y + ( this -> shape.getGlobalBounds ().height / 2.f ) - this -> text.getGlobalBounds ().height / 2.f
    );

    this -> text_idle_color = text_idle_color;
    this -> text_hover_color = text_hover_color;
    this -> text_active_color = text_active_color;

    this -> idle_color = idle_color;
    this -> hover_color = hover_color;
    this -> active_color = active_color;
}

Button::~Button ( void )
{
    
}

//Accessors

const bool Button::is_pressed ( void ) const
{
    if ( this -> Button_States == BTN_ACTIVE )
        return true;

    return false;
}

//Functions

void Button::update ( const sf::Vector2f mouse_pos )
{
    //Update the bollean hover and pressed

    //Idle
    this -> Button_States = BTN_IDLE;

    //Hover
    if ( this -> shape.getGlobalBounds ().contains ( mouse_pos ) )
    {
        this -> Button_States = BTN_HOVER;

        //Pressed
        if ( sf::Mouse::isButtonPressed ( sf::Mouse::Left ) )
        {
            this -> Button_States = BTN_ACTIVE;
        }
    }

    switch ( this -> Button_States )
    {
        case BTN_IDLE:
            this -> shape.setFillColor ( this -> idle_color );
            this -> text.setFillColor ( this -> text_idle_color );
            break;

        case BTN_HOVER:
            this -> shape.setFillColor ( this -> hover_color );
            this -> text.setFillColor ( this -> text_hover_color );
            break;

        case BTN_ACTIVE:
            this -> shape.setFillColor ( this -> active_color );
            this -> text.setFillColor ( sf::Color::Blue );
            break;
    
    default:
        this -> shape.setFillColor ( sf::Color::Red );
        break;
    }
}

void Button::render ( sf::RenderTarget& target )
{
    target.draw ( this -> shape );
    target.draw ( this -> text );
}