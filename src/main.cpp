#include <game_controller.hpp>
#include <pawn.hpp>

int main(){
    Player J1(false);

    J1.addPiece(std::make_unique<Pawn>(false,Coordinates{0,1}));


    return 0;
}