#include "button.hpp"

Button::Button()
{

}

Button::Button(float x,float y,float width,float height,const std::string &label)
{
    bounds={x,y,width,height};
    text=label;

    normalColor=DARKGRAY;
    hoverColor=LIGHTGRAY;
    textColor=BLACK;
}

void Button::draw()
{
    Vector2 mouse =  GetMousePosition();
    bool hover = CheckCollisionPointRec(mouse,bounds);

    DrawRectangleRec(bounds,hover ? hoverColor : normalColor);
    int fontSize=25;
    int textWidth=MeasureText(text.c_str(),fontSize);

    DrawText(text.c_str(),
            bounds.x+bounds.width/2-textWidth/2,
            bounds.y+bounds.height/2-fontSize/2,
            fontSize,
            textColor);
}

bool Button::isClicked()
{
    Vector2 mouse = GetMousePosition();
    bool hover = CheckCollisionPointRec(mouse,bounds);

    return hover && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}

Button::~Button()
{
    std::cout<<"bouton detruit\n";
}