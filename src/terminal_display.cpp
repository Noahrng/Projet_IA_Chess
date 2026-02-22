#include "terminal_display.hpp"
#include <iostream>


TerminalDisplay::TerminalDisplay(GameController &game,bool s): Display(game,s){

}

void TerminalDisplay::printBoard()
{
    bool color_turn = game.blackTurn();
    if(!color_turn) std::cout<< "\033[47;30m";
    else std::cout << "\033[40;37m";
    
    std::cout << "\033[0m\n";
    for(int i = 0; i < 8 ; ++i)
    {
        if(side)   std::cout << " " << i+1;
        else        std::cout << " " << 9-(i+1);

        for(int j = 0 ; j < 8 ; ++j)
        {
            Coordinates c;
            if(!side)   c.setXY(j,i);
            else        c.setXY(7-j,7-i);

            Piece * p;
            if((i+j)%2==0){
                std::cout << "\033[48;2;245;222;179m";
            }
            else{
                std::cout << "\033[48;2;34;139;34m";
            }

            Player &p1=game.getCurrentPlayer();
            Player &p2=game.getWaitingPlayer();

            if( (p=p1.getPiece(c)) != nullptr){
                if(!color_turn){
                    std::cout << "\033[97m" << p->getTerminalSprite() << " \033[0m";
                }
                else{
                    std::cout << "\033[30m" << p->getTerminalSprite() << " \033[0m";
                }
            }
            else if((p=p2.getPiece(c)) != nullptr){
                if(color_turn){
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
    std::cout << "  ";
    for(int j = 0 ; j < 8 ; ++j)
    {
        char letter;
        if(side)
        {
            letter = 'h' - j;
        }
        else
        {
            letter = 'a' + j;
        }
        std::cout << letter << " ";
    }
    std::cout << "\n";
}


void TerminalDisplay::clearTerminal()
{
    std::cout << "\x1B[2J\x1B[H";
}

void TerminalDisplay::run()
{
    while(1)
    {
        clearTerminal();
        printBoard();
        std::string coords;
        Coordinates c;
        bool coords_onboard;
        bool got_moved = false;
        bool cancel_move;
        

        while(!got_moved){
            coords_onboard = false;
            cancel_move = false;
            while(!coords_onboard)
            {
                std::cout << "Entrez les coordonnées d'une de vos pièces :\n";
                coords = game.enterPlayerCoordinates();
                c=game.convertStringIntoCoords(coords);
                if(c.onBoard())
                {
                    coords_onboard = true;
                }
            }

            game.choosePiece(c);

            while(!got_moved && !cancel_move)
            {
                std::cout << "Entrez les coordonnées pour déplacer votre pièce (cancel si vous voulez annulez votre coup) :\n";
                coords = game.enterPlayerCoordinates();
                if(game.moveCancelled(coords)) cancel_move = true;
                else
                {
                    c=game.convertStringIntoCoords(coords);
                    if(!c.onBoard()) std::cout << "Coordonnées invalides !\n";
                    else got_moved = game.movePiece(game.getCoordsPieceChosen(),c);
                }
            }
        }

        game.switchTurn();
    }    
}