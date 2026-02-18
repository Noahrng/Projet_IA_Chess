#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <raylib-5.5_linux_amd64/include/raylib.h>
#include <button.hpp>
#include <vector>

class Screen
{
    private:
        std::vector<Button>> t;
    public:
        virtual void update()=0;
        virtual void draw()=0;
};

#endif