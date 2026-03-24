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
        //Constructeurs / Destructeurs
        TextShape(std::unique_ptr<Shape>,const std::string&);

        //Setters
        void setText(const std::string&);
        void setTextColor(Color);
        void setFontSize(int);
        void setCentered(bool);

        //Dessiner le Texte
        void draw();
};

#endif