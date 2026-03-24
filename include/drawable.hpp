#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

#include <raylib.h>

class Drawable
{
    public:
        //Constructeurs / Destructeurs
        virtual ~Drawable()=default;

        //Getters
        virtual float getCenterX() = 0;
        virtual float getCenterY() = 0;
        virtual float getWidth() = 0;
        virtual float getHeight() = 0;

        //Setters
        virtual void setBackgroundColor(Color) = 0;   

        //Vérification d'État
        virtual bool isHovered(Vector2 mouse) = 0;   

        //Dessiner le Cercle
        virtual void draw() = 0;  
};

#endif