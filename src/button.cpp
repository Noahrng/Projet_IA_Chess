#include "button.hpp"

Button::Button(std::unique_ptr<Drawable> d,const std::string& text)
    :drawable{std::move(d)},text{text},normalColor{DARKGRAY},hoverColor{LIGHTGRAY},textColor{BLACK},fontSize{25}
{

}

void Button::setNormalColor(Color c)
{
    normalColor=c;
}

void Button::setHoverColor(Color c)
{
    hoverColor = c;
}

void Button::setTextColor(Color c)
{
    textColor = c;
}

void Button::setFontSize(int s)
{
    fontSize=s;
}

void Button::draw()
{
    if(this->isHovered())
    {
        drawable->setBackgroundColor(hoverColor);
    }
    else
    {
        drawable->setBackgroundColor(normalColor);
    }
        drawable->draw();

    int textWidth = MeasureText(text.c_str(),fontSize);
    DrawText(text.c_str(),(int)drawable->getCenterX()-textWidth/2,(int)drawable->getCenterY()-fontSize/2,fontSize,textColor);
}

bool Button::isHovered()
{
    return drawable->isHovered(GetMousePosition());
}

bool Button::isClicked()
{
    return isHovered() && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}

Button::~Button()
{
}