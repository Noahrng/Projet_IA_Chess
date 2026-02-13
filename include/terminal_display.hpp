#ifndef TERMINAL_DISPLAY_HPP
#define TERMINAL_DISPLAY_HPP

#include "display.hpp"
#include "player.hpp"

class TerminalDisplay : public Display{
    private: 
    public:
        TerminalDisplay(Player&, Player&, bool);
        void printBoard();
};

#endif