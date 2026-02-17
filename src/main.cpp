#include <game_controller.hpp>
#include <pawn.hpp>
#include "terminal_display.hpp"
#include <graphic_display.hpp>

int main(){
    GameController play;

    std::string test=play.enterPlayerCoordinates();
    std::cout<<test<<"\n";
    std::cout<<"♔"<<'\n';

    play.switchTurn();
    play.switchTurn();

    Coordinates test2=play.convertStringIntoCoords(test);
    test2.print();
    play.choosePiece(test2);
    std::cout<<play.isNull()<<"\n";

    Coordinates c_from(0,6);
    Coordinates c_to(0,4);
    
    play.movePiece(c_from,c_to);

    TerminalDisplay t(play,0);
    t.printBoard();
    
    GraphicDisplay gp1(1000,1000,"CHESS",play,0);
    
    gp1.run();
    std::cout<<"test\n";



   
    
    return 0;
}