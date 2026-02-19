#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <raylib-5.5_linux_amd64/include/raylib.h>
#include <memory>
#include "game_controller.hpp"

class Screen
{
    protected:
        GameController& game;
            
    public:
        Screen(GameController &g):game(g){}
        virtual ~Screen()=default;

        virtual void update()=0;
        virtual void draw()=0;

        virtual bool isFinished()=0;
        virtual std::unique_ptr<Screen> nextScreen()=0;
};

#endif