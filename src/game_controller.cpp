#include <game_controller.hpp>
GameController::GameController()
{
    current_player = new Player(false);
    waiting_player = new Player(true);
    piece_chosen = nullptr;
}

GameController::~GameController()
{
    delete current_player;
    delete waiting_player;
}

bool operator==(const GameController &a,const GameController &b)
{
    return ( (*(a.current_player) == *(b.current_player) && 
    *(a.waiting_player)==*(b.waiting_player)) ||
    (*(a.waiting_player)==*(b.current_player) && 
    *(a.current_player)==*(b.waiting_player)) );
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

    int dx = from.distX(to);
    int dy = from.distY(to);

    int step_x=0; 
    int step_y=0;

    if(dx == 0 && dy != 0)
    {
        if(from.lowerThanY(to)) step_y = 1;
        else step_y = -1;
    }
    else if(dx != 0 && dy == 0)
    {
        if(from.lowerThanX(to)) step_x = 1;
        else step_x = -1;
    }
    else if(dx == dy)
    {
        if(from.lowerThanX(to)) step_x = 1;
        else step_x = -1;
        if(from.lowerThanY(to)) step_y = 1;
        else step_y = -1;
    }
    else
    {
        return false;
    }

    int i = from.getY() + step_y;
    int j = from.getX() + step_x;

    std::cout << "[DEBUG] condition: x=" << to.getX() << " y=" << to.getY() << "\n";
    while(j != to.getX() || i != to.getY()){
        Coordinates c(j,i);
        std::cout << "[DEBUG] i = " << i << ", j = " << j << "\n";
        if(current_player->getPiece(c)  ||
        waiting_player->getPiece(c))
        {
            std::cout << c << "\n";
            return true;
        }
        i += step_y;
        j += step_x;
    }
    return false;
}



bool GameController::canMovePiece(Coordinates from, Coordinates to)
{
    if(!from.onBoard() || !to.onBoard()) return false;  
    return true;
}
