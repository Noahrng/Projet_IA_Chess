#include <game_controller.hpp>
#include <pawn.hpp>
#include "terminal_display.hpp"
#include <graphic_display.hpp>

int main(){
    GameController play;

    std::string test=play.enterPlayerCoordinates();
    std::cout<<test<<"\n";

    play.switchTurn();
    play.switchTurn();

    Coordinates test2=play.convertStringIntoCoords(test);
    test2.print();
    play.choosePiece(test2);
    std::cout<<play.isNull()<<"\n";
    
    Coordinates c_from(0,6);
    Coordinates c_to(0,4);
    play.movePiece(c_from,c_to);
    std::cout << "Test après premier move\n";

    c_from.setXY(0,4);
    c_to.setXY(0,3);

    play.movePiece(c_from,c_to);
    std::cout << "Test après premier move\n";

    c_from.setXY(0,3);
    c_to.setXY(0,2);

    play.movePiece(c_from,c_to);
    std::cout << "Test après premier move\n";

    std::cout << "menacée :" << play.isThreaten(c_to) << "\n";

    TerminalDisplay t(play,0);
    t.printBoard();
    
    GraphicDisplay gp1(1000,1000,"CHESS",play,0);
    
    gp1.run();
    std::cout<<"test\n";



   
    
    return 0;
}