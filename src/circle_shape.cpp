#include "circle_shape.hpp"

/*----------------------Constructeurs / Destructeurs----------------------*/
CircleShape::CircleShape(float x,float y,float radius)
    :Shape(x,y),radius{radius}
{

}

/*--------------------------------Getters---------------------------------*/
float CircleShape::getCenterX() 
/*
    Description:
        retourne l'absice du centre du cercle
*/
{ 
    return x; 
}
float CircleShape::getCenterY() 
/*
    Description:
        retourne l'ordonnée du centre du cercle
*/
{ 
    return y; 
}

float CircleShape::getWidth()  
/*
    Description:
        retourne la largeur du cercle
    Note:
        ici largeur = hauteur comme c'est un cercle
*/
{   
    return radius * 2; 
}
float CircleShape::getHeight() 
/*
    Description:
        retourne la hauteur du cercle du cercle
    Note:
        ici largeur = hauteur comme c'est un cercle
*/
{   
    return radius * 2; 
}

/*--------------------------Vérification d'État---------------------------*/
bool CircleShape::isHovered(Vector2 mouse)
/*
    Description:
        retourne si le cercle est survolé avec la souris
*/
{
    return CheckCollisionPointCircle(mouse, {x, y}, radius);
}

/*--------------------------Dessiner le Cercle----------------------------*/
void CircleShape::draw()
/*
    Description:
        Affiche le cercle
*/
{
    DrawCircle((int)x,(int)y,radius,backgroundColor);
    if(borderThickness > 0)
    {
        DrawCircleLines((int)x,(int)y,radius,borderColor);
    }
}
