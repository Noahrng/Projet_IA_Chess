#ifndef CIRCLE_SHAPE_HPP
#define CIRCLE_SHAPE_HPP

#include "shape.hpp"

class CircleShape : public Shape
{
    protected:
        float radius;
    public:
        CircleShape(float,float,float);
        void draw() override;
        bool isHovered(Vector2 mouse) override;
        float getCenterX() override;
        float getCenterY() override;
        float getWidth() override;
        float getHeight() override;
};

#endif