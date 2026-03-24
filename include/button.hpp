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
        //Constructeurs / Destructeurs
        Button(std::unique_ptr<Drawable>,const std::string&);
        ~Button();

        //Setters
        void setNormalColor(Color);
        void setHoverColor(Color);
        void setTextColor(Color);
        void setFontSize(int);
    
        //Vérification d'État
        bool isClicked();
        bool isHovered();

        //Dessiner le Bouton
        void draw();
        
};

#endif