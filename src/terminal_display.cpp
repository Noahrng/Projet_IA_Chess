#include "terminal_display.hpp"
#include <iostream>


TerminalDisplay::TerminalDisplay(Player &j1, Player &j2): p1(j1),p2(j2){

}

void TerminalDisplay::printBoard()
{
    for(int i = 0; i < 8 ; ++i)
    {
        for(int j = 0 ; j < 8 ; ++j)
        {
            if((i+j)%2==0){
                std::cout << "\033[47m";
            }
            else{
                std::cout << "\033[40m";
            }

            std::cout << "♔ \033[0m";
        }
        std::cout << "\n";
    }
}