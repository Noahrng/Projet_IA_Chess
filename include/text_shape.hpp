#ifndef TEXT_SHAPE_HPP
#define TEXT_SHAPE_HPP

#include "shape.hpp"
#include <memory>
#include <string>

class TextShape{
    private:
        std::unique_ptr<Shape> shape;
        std::string text;
        Color textColor;

        int fontSize;
        bool centered;

    public:
        TextShape(std::unique_ptr<Shape>,const std::string&);

        void setText(const std::string&);
        void setTextColor(Color);
        void setFontSize(int);
        void setCentered(bool);

        void draw();
};

#endif