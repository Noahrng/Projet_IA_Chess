#include "terminal_display.hpp"
#include <iostream>


TerminalDisplay::TerminalDisplay(GameController &game,bool s): Display(game,s){

}

void TerminalDisplay::printBoard()
{
    for(int i = 0; i < 8 ; ++i)
    {
        for(int j = 0 ; j < 8 ; ++j)
        {
            Coordinates c;
            if(!side) c.setXY(j,i);
            else c.setXY(7-j,7-i);
            Piece * p;
            if((i+j)%2==0){
                std::cout << "\033[48;2;245;222;179m";
            }
            else{
                std::cout << "\033[48;2;34;139;34m";
            }

            Player &p1=game.getJ1();
            Player &p2=game.getJ2();

            if( (p=p1.getPiece(c)) != nullptr){
                if(p1.isWhite()){
                    std::cout << "\033[97m" << p->getTerminalSprite() << " \033[0m";
                }
                else{
                    std::cout << "\033[30m" << p->getTerminalSprite() << " \033[0m";
                }
            }
            else if((p=p2.getPiece(c)) != nullptr){
                if(p2.isWhite()){
                    std::cout << "\033[97m" << p->getTerminalSprite() << " \033[0m";
                }
                else{
                    std::cout << "\033[30m" << p->getTerminalSprite() << " \033[0m";
                }
            }
            else{
                std::cout << "  ";
            }

            std::cout << "\033[0m";
        }
        std::cout << "\n";
    }
}