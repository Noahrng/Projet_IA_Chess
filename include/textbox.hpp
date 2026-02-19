#ifndef TEXTBOX_HPP
#define TEXTBOX_HPP

#include <raylib-5.5_linux_amd64/include/raylib.h>
#include <string>

class TextBox{
    private:
        Rectangle bounds;

        std::string text;

        Color backgroundColor;
        Color textColor;

        int fontSize;
        bool centered;

    public:
        TextBox(float,float,float,float,const std::string&);

        void setText(const std::string&);
        void setBackgroundColor(Color);
        void setTextColor(Color);
        void setFontSize(int);
        void setCentered(bool);

        void draw();
};

#endif