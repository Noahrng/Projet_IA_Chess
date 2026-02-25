#include "button.hpp"

Button::Button(std::unique_ptr<Shape> s,const std::string& text)
    :shape{std::move(s)},text{text},normalColor{DARKGRAY},hoverColor{LIGHTGRAY},textColor{BLACK},fontSize{25}
{

}

void Button::SetnormalColor(Color c)
{
    normalColor=c;
}

void Button::SetHoverColor(Color c)
{
    hoverColor = c;
}

void Button::SetTextColor(Color c)
{
    textColor = c;
}

void Button::SetFontSize(int s)
{
    fontSize=s;
}

void Button::draw()
{
    if(this->isHovered())
    {
        shape->setBackgroundColor(hoverColor);
    }
    else
    {
        shape->setBackgroundColor(normalColor);
    }
    shape->draw();

    int textWidth = MeasureText(text.c_str(),fontSize);
    DrawText(text.c_str(),(int)shape->getCenterX()-textWidth/2,(int)shape->getCenterY()-fontSize/2,fontSize,textColor);
}

bool Button::isHovered()
{
    return shape->isHovered(GetMousePosition());
}

bool Button::isClicked()
{
    Vector2 mouse = GetMousePosition();
    return shape->isHovered(mouse) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}

Button::~Button()
{
}