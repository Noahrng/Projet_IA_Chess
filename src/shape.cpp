#include "shape.hpp"

/*----------------------Constructeurs / Destructeurs----------------------*/
Shape::Shape(float x,float y)
    :x{x},y{y},backgroundColor{LIGHTGRAY},borderColor{BLACK},borderThickness{0}
{

}

/*--------------------------------Setters---------------------------------*/
void Shape::setBackgroundColor(Color c)
/*
    Description:
        Change la couleur d'arrière plan
*/
{
    backgroundColor = c;
}

void Shape::setBorderColor(Color c)
/*
    Description:
        Change la couleur de la bordure
*/
{
    borderColor=c;
}

void Shape::setBorderThickness(float t)
/*
    Description:
        Change l'épaisseur de la bordure
*/
{
    borderThickness=t;
}