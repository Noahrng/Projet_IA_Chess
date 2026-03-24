#include "circle_shape.hpp"

/*----------------------Constructeurs / Destructeurs----------------------*/
CircleShape::CircleShape(float x,float y,float radius)
    :Shape(x,y),radius{radius}
{

}

/*--------------------------------Getters---------------------------------*/
float CircleShape::getCenterX() 
{ 
    return x; 
}
float CircleShape::getCenterY() 
{ 
    return y; 
}

float CircleShape::getWidth()  
{   
    return radius * 2; 
}
float CircleShape::getHeight() 
{   
    return radius * 2; 
}

/*--------------------------Vérification d'État---------------------------*/
bool CircleShape::isHovered(Vector2 mouse)
{
    return CheckCollisionPointCircle(mouse, {x, y}, radius);
}

/*--------------------------Dessiner le Cercle----------------------------*/
void CircleShape::draw()
{
    DrawCircle((int)x,(int)y,radius,backgroundColor);
    if(borderThickness > 0)
    {
        DrawCircleLines((int)x,(int)y,radius,borderColor);
    }
}
