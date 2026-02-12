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
    int i= -1;
    int j= -1;
    if(move.length() == 2){
        if(isLetter(move[1]) && isNumber(move[0])){
            if(move[1] <= 'h'){
                j=move[1] - 'a';
            }
            if(move[0] >= '1' && move[0] <= '8'){
                i = move[0] - '1';
            }
        }
        else if (isLetter(move[0]) && isNumber(move[1]))
        {
            if(move[0] <= 'h'){
                j=move[0] - 'a';
            }
            if(move[1] >= '1' && move[1] <= '8'){
                i = move[1] - '1';
            }
        }
    }

    Coordinates c(j,i);

    return c;
}