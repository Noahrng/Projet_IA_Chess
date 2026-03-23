#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include "game_controller.hpp"
#include "minimax.hpp"

class Display{
    protected:
        GameController &game;
        Minimax &robot;
        bool side; //0: blancs en bas, 1: noir en bas
    public:
        Display(GameController&,Minimax&,bool);
};

#endif