#include "textbox.hpp"

TextBox::TextBox(float x,float y,float width,float height,const std::string &text):bounds{x,y,width,height},
                                                                                   text{text},
                                                                                   backgroundColor(LIGHTGRAY),
                                                                                   textColor(BLACK),
                                                                                   fontSize(20),
                                                                                   centered(true)
{

}

void TextBox::setText(const std::string& newText)
{
    text=newText;
}
void TextBox::setBackgroundColor(Color color)
{
    backgroundColor=color;
}
void TextBox::setTextColor(Color color)
{
    textColor=color;
}
void TextBox::setFontSize(int size)
{
    fontSize=size;
}
void TextBox::setCentered(bool value)
{
    centered=value;
}
void TextBox::draw()
{
    DrawRectangleRec(bounds,backgroundColor);

    int textWidth=MeasureText(text.c_str(),fontSize);

    float textX;
    float textY=bounds.y+(bounds.height-fontSize)/2;

    if(centered)
    {
        textX=bounds.x+(bounds.width-textWidth);
    }
    else
    {
        textX=bounds.x+5;
    }

    DrawText(text.c_str(),static_cast<int>(textX),static_cast<int>(textY),fontSize,textColor);
}
