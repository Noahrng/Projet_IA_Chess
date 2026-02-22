#include "terminal_display.hpp"
#include <iostream>


TerminalDisplay::TerminalDisplay(GameController &game,bool s): Display(game,s){

}

void TerminalDisplay::printBoard()
{
    bool color_turn = game.blackTurn();
    std::string colored_cell;
    std::string end_color = "\033[0m";

    if(!color_turn)
    {
        colored_cell = "\033[47;30m";
        std::cout<< colored_cell << "    White's Turn    ";
    } 
    else{
        colored_cell = "\033[40;37m"; 
        std::cout << colored_cell << "    Black's Turn    ";
    }
    
    std::cout << end_color << std::endl ;
    for(int i = 0; i < 8 ; ++i)
    {
        if(side)   std::cout << colored_cell << " " << i+1 << end_color;
        else        std::cout << colored_cell << " " << 9-(i+1) << end_color;

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
                    std::cout << "\033[97m" << p->getTerminalSprite() << " " << end_color;
                }
                else{
                    std::cout << "\033[30m" << p->getTerminalSprite() << " " << end_color;
                }
            }
            else if((p=p2.getPiece(c)) != nullptr){
                if(color_turn){
                    std::cout << "\033[97m" << p->getTerminalSprite() << " " << end_color;
                }
                else{
                    std::cout << "\033[30m" << p->getTerminalSprite() << " " << end_color;
                }
            }
            else{
                std::cout << "  ";
            }

            std::cout << "\033[0m";
        }
        std::cout << colored_cell << "  " << end_color <<  "\n";
    }
    std::cout << colored_cell << "  ";
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
    std::cout << "  " << end_color << "\n";
}


void TerminalDisplay::clearTerminal()
{
    std::cout << "\x1B[2J\x1B[H";
}

void TerminalDisplay::run()
{
    while(1)
    {
        std::string coords;
        Coordinates c;
        std::string error_color = "\033[41;37m";
        std::string end_color = "\033[0m";
        bool coords_onboard;
        bool got_moved = false;
        bool cancel_move;
        bool piece_belong_to;
        

        while(!got_moved){
            clearTerminal();
            printBoard();
            coords_onboard = false;
            cancel_move = false;
            piece_belong_to = false;

            while(!coords_onboard || !piece_belong_to)
            {
                std::cout << "Entrez les coordonnées d'une de vos pièces :\n";
                coords = game.enterPlayerCoordinates();
                c=game.convertStringIntoCoords(coords);
                if(c.onBoard())
                {
                    coords_onboard = true;
                    game.choosePiece(c);
                    if(!game.isNull())
                    {
                        piece_belong_to = true;
                    }
                    else
                    {
                        std::cout << error_color <<
                        "/!\\ Coordonnées invalides, il n'y a pas de pièce qui vous appartient.\n"
                        << end_color;
                    }
                }
                else
                {
                    std::cout << error_color <<
                    "/!\\ Coordonnées invalides, elles ne sont pas sur le plateau !\n"
                    << end_color;

                }
            }


            while(!got_moved || cancel_move)
            {
                std::cout << "Entrez les coordonnées pour déplacer votre pièce (cancel si vous voulez annulez votre coup) :\n";
                coords = game.enterPlayerCoordinates();
                if(game.moveCancelled(coords)) cancel_move = true;
                else
                {
                    c=game.convertStringIntoCoords(coords);
                    got_moved = game.movePiece(game.getCoordsPieceChosen(),c);
                    if(!c.onBoard() || !got_moved) 
                        std::cout << error_color << 
                        "/!\\ Coordonnées invalides, vous ne pouvez pas bouger ici !\n"
                        << end_color;
                }
            }
        }

        game.switchTurn();
    }    
}