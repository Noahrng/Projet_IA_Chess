#include "text_shape.hpp"

/*----------------------Constructeurs / Destructeurs----------------------*/
TextShape::TextShape(std::unique_ptr<Shape> s,const std::string &text)
    :shape{std::move(s)},text{text},textColor{BLACK},fontSize{20},centered{true}
{

}

/*--------------------------------Setters---------------------------------*/
void TextShape::setText(const std::string& newText)
{
    text=newText;
}

void TextShape::setTextColor(Color color)
{
    textColor=color;
}

void TextShape::setFontSize(int size)
{
    fontSize=size;
}
void TextShape::setCentered(bool value)
{
    centered=value;
}

/*---------------------------Dessiner le Texte----------------------------*/
void TextShape::draw()
{
    shape->draw();

    // Réduit le fontSize jusqu'à ce que le texte rentre
    int currentFontSize = fontSize;
    float maxWidth = shape->getWidth() - 10;  // marge de 5px de chaque côté

    int textWidth = MeasureText(text.c_str(), currentFontSize);
    while(textWidth > maxWidth && currentFontSize > 5)
    {
        currentFontSize--;
        textWidth = MeasureText(text.c_str(), currentFontSize);
    }

    float textX;
    float textY = shape->getCenterY() - currentFontSize / 2;

    if(centered)
        textX = shape->getCenterX() - textWidth / 2;
    else
        textX = shape->getCenterX() - shape->getWidth() / 2 + 5;

    DrawText(text.c_str(), (int)textX, (int)textY, currentFontSize, textColor);
}