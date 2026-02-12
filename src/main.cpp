#include <game_controller.hpp>
#include <pawn.hpp>
#include "terminal_display.hpp"

int main(){
    GameController play;

    std::string test=play.enterPlayerMovement();
    std::cout<<test<<"\n";
    std::cout<<"♔"<<'\n';


    Player j1(0);
    Player j2(1);
    TerminalDisplay t(j1,j2);
    t.printBoard();
    return 0;
}