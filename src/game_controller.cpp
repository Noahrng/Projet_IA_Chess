#include <game_controller.hpp>
GameController::GameController():j1{false},j2{true},current_player{j1}{

}
//GameController::GameController(Player* p1, Player* p2) : j1(p1), j2(p2) {}

//Entrées joueur
std::string GameController::enterPlayerMovement(){
    std::string entry;
    std::cout<<"entre où veut tu deplacer la pièce"<<std::endl;
    std::cin>>entry;
    return entry;
} 

bool isLetter(char c)
{
    return (c >= 'a' && c<='z') || (c >= 'A' && c<= 'Z');
}

bool isNumber(char c)
{
    return (c >= '0' && c<='9');
}

/* Coordinates convertStringIntoCoords(std::string move)
{
    if(move.length() == 2){
        int i;
        int j;
        if(isLetter(move[0])){
            
        }
    }


} */