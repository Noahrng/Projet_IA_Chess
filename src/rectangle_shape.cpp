#include "rectangle_shape.hpp"

/*----------------------Constructeurs / Destructeurs----------------------*/
RectangleShape::RectangleShape(float x,float y,float width,float height)
    :Shape(x,y), width{width}, height{height}
{

}

/*--------------------------------Getters---------------------------------*/
float RectangleShape::getCenterX()
{ 
    return x + width / 2; 
}
float RectangleShape::getCenterY() 
{ 
    return y + height / 2; 
}

float RectangleShape::getWidth()  
{
     return width; 
}
float RectangleShape::getHeight() 
{
     return height; 
}

/*--------------------------Vérification d'État---------------------------*/
bool RectangleShape::isHovered(Vector2 mouse)
{
    return CheckCollisionPointRec(mouse, {x, y, width, height});
}

/*-------------------------Dessiner le Rectangle--------------------------*/
void RectangleShape::draw()
{
    DrawRectangle((int)x,(int)y,(int)width,(int)height,backgroundColor);
    if(borderThickness>0)
    {
        DrawRectangleLinesEx({x,y,width,height},borderThickness,borderColor);
    }
}