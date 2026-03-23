#ifndef SHAPE_HPP
#define SHAPE_HPP 

#include <raylib.h>
#include "drawable.hpp"

class Shape : public Drawable
{
    protected:
        float x,y;
        Color backgroundColor;
        Color borderColor;
        float borderThickness;    
    public:
        Shape(float,float);
        virtual ~Shape()=default;

        void setBackgroundColor(Color) override;
        void setBorderColor(Color);
        void setBorderThickness(float);

        virtual void draw()=0;
        virtual bool isHovered(Vector2 mouse)=0;
        virtual float getCenterX()=0;
        virtual float getCenterY()=0;
        virtual float getWidth()=0;
        virtual float getHeight()=0;

};

#endif