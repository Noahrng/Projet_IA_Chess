#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "shape.hpp"
#include <memory>
#include <string>

class Button
{
    private:
        std::unique_ptr<Drawable> drawable;
        std::string text;
        Color normalColor;
        Color hoverColor;
        Color textColor;
        int fontSize;
    public:
        Button(std::unique_ptr<Drawable>,const std::string&);
        ~Button();

        void SetnormalColor(Color);
        void SetHoverColor(Color);
        void SetTextColor(Color);
        void SetFontSize(int);
    

        bool isClicked();
        bool isHovered();

        void draw();
        
};

#endif