#include <game_controller.hpp>
#include <pawn.hpp>

int main(){
    GameController play;

    std::string test=play.enterPlayerCoordinates();
    std::cout<<test<<"\n";

    return 0;
}