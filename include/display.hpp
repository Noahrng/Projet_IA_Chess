#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include "game_controller.hpp"

class Display{
    protected:
        GameController &game;
        bool side; //0: blancs en bas, 1: noir en bas
    public:
        Display(GameController&,bool);
};

#endif