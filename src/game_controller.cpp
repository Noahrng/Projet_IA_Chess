#include <game_controller.hpp>
GameController::GameController(): j1(true), j2(false), current_player(&j1), piece_chosen(nullptr)
{
}

//GameController::GameController(Player* p1, Player* p2) : j1(p1), j2(p2) {}

//Entrées joueur
std::string GameController::enterPlayerCoordinates()
{
    std::string entry;
    std::cout<<"entre les coordonnée sur l'echiquier"<<std::endl;
    std::cin>>entry;
    return entry;
} 

void GameController::choosePiece(Coordinates c)
{
    this->piece_chosen=current_player->getPiece(c);
}

void GameController::switchTurn()
{
    if(current_player==&j1) current_player=&j2;
    else current_player=&j1;
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
                i = 7- (move[0] - '1');
            }
        }
        else if (isLetter(move[0]) && isNumber(move[1]))
        {
            if(move[0] <= 'h'){
                j=move[0] - 'a';
            }
            if(move[1] >= '1' && move[1] <= '8'){
                i = 7-(move[1] - '1');
            }
        }
    }

    Coordinates c(j,i);

    return c;
}

bool GameController::isNull(){
    return piece_chosen==nullptr;
}