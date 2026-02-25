#ifndef RECTANGLE_SHAPE_HPP
#define RECTANGLE_SHAPE_HPP

#include "shape.hpp"

class RectangleShape : public Shape
{
    protected:
        float width,height;
    public:
        RectangleShape(float,float,float,float);
        void draw() override;
        bool isHovered(Vector2 mouse) override;
        float getCenterX() override;
        float getCenterY() override;
        float getWidth() override;
        float getHeight() override;
};

#endif