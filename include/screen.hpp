#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <raylib.h>
#include <memory>
#include "game_controller.hpp"
#include "minimax.hpp"

class Screen
{
    protected:
        GameController& game;
        Minimax& robot;
            
    public:
        Screen(GameController &g,Minimax &r):game(g),robot{r}
        {}
        virtual ~Screen()=default;

        virtual void update()=0;
        virtual void draw()=0;

        virtual bool isFinished()=0;
        virtual std::unique_ptr<Screen> nextScreen()=0;
};

#endif