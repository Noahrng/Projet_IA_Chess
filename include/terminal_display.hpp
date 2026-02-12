#ifndef TERMINAL_DISPLAY_HPP
#define TERMINAL_DISPLAY_HPP

#include "display.hpp"
#include "player.hpp"

class TerminalDisplay : public Display{
    private: 
        Player &p1;
        Player &p2;
    public:
        TerminalDisplay(Player&, Player&);
        void printBoard();
};

#endif