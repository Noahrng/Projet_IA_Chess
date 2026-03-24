#ifndef CIRCLE_SHAPE_HPP
#define CIRCLE_SHAPE_HPP

#include "shape.hpp"

class CircleShape : public Shape
{
    protected:
        float radius;
    public:
        //Constructeurs / Destructeurs
        CircleShape(float,float,float);

        //Getters
        float getCenterX() override;
        float getCenterY() override;
        float getWidth() override;
        float getHeight() override;

        //Vérification d'État
        bool isHovered(Vector2 mouse) override;
        
        //Dessiner le Cercle
        void draw() override;
};

#endif