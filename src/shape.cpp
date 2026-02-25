#include "shape.hpp"

Shape::Shape(float x,float y)
    :x{x},y{y},backgroundColor{LIGHTGRAY},borderColor{BLACK},borderThickness{0}
{

}

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