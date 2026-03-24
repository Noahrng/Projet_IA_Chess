#include "shape.hpp"

/*----------------------Constructeurs / Destructeurs----------------------*/
Shape::Shape(float x,float y)
    :x{x},y{y},backgroundColor{LIGHTGRAY},borderColor{BLACK},borderThickness{0}
{

}

/*--------------------------------Setters---------------------------------*/
void Shape::setBackgroundColor(Color c)
{
    backgroundColor = c;
}

void Shape::setBorderColor(Color c)
{
    borderColor=c;
}

void Shape::setBorderThickness(float t)
{
    borderThickness=t;
}