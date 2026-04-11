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
        Retourne l'abscisse du centre du cercle
*/
{ 
    return x; 
}
float CircleShape::getCenterY() 
/*
    Description:
        Retourne l'ordonnée du centre du cercle
*/
{ 
    return y; 
}

float CircleShape::getWidth()  
/*
    Description:
        Retourne la largeur du cercle
    Note:
        ici largeur = hauteur comme c'est un cercle
*/
{   
    return radius * 2; 
}
float CircleShape::getHeight() 
/*
    Description:
        Retourne la hauteur du cercle 
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
        Retourne si le cercle est survolé avec la souris
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
