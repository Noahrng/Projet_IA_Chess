#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include "player.hpp"

class Display{
    protected:
        Player &p1;
        Player &p2;
        bool side; //0: blancs en bas, 1: noir en bas
    public:
        Display(Player&, Player&, bool);
};

#endif