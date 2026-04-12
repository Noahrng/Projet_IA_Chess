#include "button.hpp"

/*----------------------Constructeurs / Destructeurs----------------------*/
Button::Button(std::unique_ptr<Drawable> d,const std::string& text)
    :drawable{std::move(d)},text{text},normalColor{DARKGRAY},hoverColor{LIGHTGRAY},textColor{BLACK},fontSize{25}
{

}

Button::~Button()
{

}

/*--------------------------------Setters---------------------------------*/
void Button::setNormalColor(Color c)
/*
    Description:
        Affecte la couleur normale a la couleur c
*/
{
    normalColor=c;
}

void Button::setHoverColor(Color c)
/*
    Description:
        Affecte la couleur quand on survole avec la souris à la couleur c
*/
{
    hoverColor = c;
}

void Button::setTextColor(Color c)
/*
    Description:
        Affecte la couleur du texte à la couleur c
*/
{
    textColor = c;
}

void Button::setFontSize(int s)
/*
    Description:
        Affecte la couleur du texte à la couleur c
*/
{
    fontSize=s;
}

/*--------------------------Vérification d'État---------------------------*/
bool Button::isHovered()
/*
    Description:
        Renvoie si le bouton est survolé avec la souris
*/
{
    return drawable->isHovered(GetMousePosition());
}

bool Button::isClicked()
/*
    Description:
        Renvoie si le bouton est cliquer avec la souris
*/
{
    return isHovered() && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}

/*--------------------------Dessiner le Bouton----------------------------*/
void Button::draw()
/*
    Description:
        Affiche le bouton
*/
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