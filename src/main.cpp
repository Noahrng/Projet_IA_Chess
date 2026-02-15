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

    


    Player j1(0);
    Player j2(1);
    TerminalDisplay t(j1,j2,1);
    t.printBoard();
    
    GraphicDisplay gp1(800,800,"CHESS",j1,j2,1);
    
    gp1.run();
    std::cout<<"test\n";



   
    
    return 0;
}