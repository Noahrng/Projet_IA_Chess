#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <string>
#include <raylib-5.5_linux_amd64/include/raylib.h>
#include <iostream>
class Button
{
    private:
        Rectangle bounds;
        std::string text;

        Color normalColor;
        Color hoverColor;
        Color textColor;
    public:
        Button();
        ~Button();
        Button(float,float,float,float,const std::string&);
        void draw();
        bool isClicked();
};

#endif