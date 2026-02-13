#include <game_controller.hpp>
#include <pawn.hpp>
#include "terminal_display.hpp"
#include <raylib-5.5_linux_amd64/include/raylib.h>

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
    std::cout<<play.isnull()<<"\n";

    


    Player j1(0);
    Player j2(0);
    TerminalDisplay t(j1,j2);
    t.printBoard();

    InitWindow(500,500,"Chess");

    while(WindowShouldClose()==false){
        BeginDrawing();
        ClearBackground(GREEN);
        EndDrawing();
    }

    
    return 0;
}