#ifndef RECTANGLE_SHAPE_HPP
#define RECTANGLE_SHAPE_HPP

#include "shape.hpp"

class RectangleShape : public Shape
{
    protected:
        float width,height;
    public:
        //Constructeurs / Destructeurs
        RectangleShape(float,float,float,float);

        //Getters
        float getCenterX() override;
        float getCenterY() override;
        float getWidth() override;
        float getHeight() override;

        //Vérification d'État
        bool isHovered(Vector2 mouse) override;
        
        //Dessiner le Rectangle
        void draw() override;        
};

#endif