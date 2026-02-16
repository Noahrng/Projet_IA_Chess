#include <game_controller.hpp>
GameController::GameController()
{
    current_player = new Player(true);
    waiting_player = new Player(false);
    piece_chosen = nullptr;
}

GameController::~GameController()
{
    delete current_player;
    delete waiting_player;
}

bool operator==(const GameController &a,const GameController &b)
{
    return *(a.current_player)==*(b.current_player) && 
    *(a.waiting_player)==*(b.waiting_player) ||
    *(a.waiting_player)==*(b.current_player) && 
    *(a.current_player)==*(b.waiting_player);
}

bool operator!=(const GameController &a,const GameController &b)
{
    return !(a==b);
}

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
    auto tmp = current_player;
    current_player = waiting_player;
    waiting_player = tmp;
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


//Déplacements

bool GameController::pieceInBetween(Coordinates from, Coordinates to)
/* 
Vérifie s'il y a une pièce entre les coordonnées de départ, et les coordonnées d'arrivées. 
Ne marche que si les coordonnées de départ et d'arrivées sont en diagonales, lignes ou colonnes
*/
{
    if(!from.onBoard() || !to.onBoard()) return false;

    if(from.distX(to)  == 0 && from.distY(to) != 0){
        //Même colonne
        
    }

}

bool GameController::canMovePiece(Coordinates from, Coordinates to)
{
    if(!from.onBoard() || !to.onBoard()) return false;  
}
