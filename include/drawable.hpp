#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

#include <raylib.h>

class Drawable
{
    public:
        virtual ~Drawable()=default;

        virtual void draw() = 0;
        virtual bool isHovered(Vector2 mouse) = 0;
        virtual float getCenterX() = 0;
        virtual float getCenterY() = 0;
        virtual float getWidth() = 0;
        virtual float getHeight() = 0;
        virtual void setBackgroundColor(Color) = 0;        
};

#endif