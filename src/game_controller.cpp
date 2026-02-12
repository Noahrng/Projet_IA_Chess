#include <game_controller.hpp>

GameController::GameController(Player* p1, Player* p2) : j1(p1), j2(p2) {}


//Entrées joueur
std::string enterPlayerMovement(){
    
} 

bool GameController::isLetter(char c)
{
    return (c >= 'a' && c<='z') || (c >= 'A' && c<= 'Z');
}

bool GameController::isNumber(char c)
{
    return (c >= '0' && c<='9');
}

Coordinates GameController::convertStringIntoCoords(std::string move)
{
    int i;
    int j;
    if(move.length() == 2){
        if(isLetter(move[1]) && isNumber(move[0])
            || isLetter(move[0]) && isNumber(move[1]))
        {
            if(isLetter(move[0])){
                if(move[0] <= 'h'){
                    j=move[0] - 'a';
                }
                else{
                    j = -1;
                }
                if(move[1] >= '1' && move[1] <= '8'){
                    i = move[1] - '1';
                }
                else{
                    i= -1;
                }
            }
            else{
                if(move[1] <= 'h'){
                    j=move[1] - 'a';
                }
                else{
                    j = -1;
                }
                if(move[0] >= '1' && move[0] <= '8'){
                    i = move[0] - '1';
                }
                else{
                    i= -1;
                }
            }
        }
        else{
            i= -1 ; j = -1;
        }
    }
    else{
        i= -1; j = -1;
    }

    Coordinates c(j,i);

    return c;
}