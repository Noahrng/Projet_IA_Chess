#include "../include/game_controller.hpp"

GameController::GameController(Player* p1, Player* p2) : j1(p1), j2(p2) {}


//Entrées joueur
std::string enterPlayerMovement(){
    
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