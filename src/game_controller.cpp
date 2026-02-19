#include <game_controller.hpp>
GameController::GameController()
{
    current_player = new Player(false);
    waiting_player = new Player(true);
    piece_chosen = nullptr;
    cell_chosen.setXY(-1,-1);
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

Player& GameController::getJ1()
{
    return *current_player;
}
Player& GameController::getJ2()
{
    return *waiting_player;
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
    
    while(j != to.getX() || i != to.getY()){
        Coordinates c(j,i);
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





bool GameController::pieceAllyDetection(Coordinates c)
{
    return current_player->getPiece(c)!=nullptr;
}
bool GameController::pieceEnemyDetection(Coordinates c)
{
    return waiting_player->getPiece(c)!=nullptr;
}

bool GameController::canMovePiece(Coordinates from, Coordinates to, bool enemy)
{
    Piece * p = nullptr;
    if(!enemy) p = current_player->getPiece(from);
    else p = waiting_player->getPiece(from);

    if(!from.onBoard() || !to.onBoard()) return false;  

    if(p == nullptr) return false;

    if(pieceInBetween(from,to)) return false;

    if(!enemy && pieceAllyDetection(to)) return false;
    
    if(enemy && pieceEnemyDetection(to)) return false;

    //Vérification si le roi est en échec si on bouge la pièce

    //Vérification si c'est le roi qu'on déplace et qu'on ne le déplace pas sur une case en échecs

    if(p->canMove(to)) return true;
    return false;
}

int GameController::isThreaten(Coordinates c)
    /* 
    Vérifie si une case aux coordonnées c est menacée ou non par une pièce 
    et renvoie le nombre de pièces qui la menace
    */    
{
    int nb_threats = 0;

    size_t i = 0;
    while(i < waiting_player->nbOfPieces())
    {
        Piece* p = waiting_player->getPiece(i);
        if(p->canMove(c) && 
        pieceInBetween(p->getCoordinates(),c)) 
        {
            nb_threats++;
        }
        i++;
    }
    return nb_threats;
}

void GameController::movePiece(Coordinates from, Coordinates to)
{
    if(canMovePiece(from,to,0)){
        Piece * p = current_player->getPiece(from);
        if(pieceEnemyDetection(to)){
            Piece * p_mangee = waiting_player->getPiece(to);
            eatPiece(p_mangee);
        }
        //Déplacer la pièce
        p->moveTo(to.getX(),to.getY());
        piece_chosen = nullptr;
        cell_chosen.setXY(-1,-1);
    }
}

void GameController::eatPiece(Piece* p)
{
    size_t i = 0;
    size_t n = waiting_player->nbOfPieces();
    while(i < n && !waiting_player->isPiece(p,i))
    {
        i++;
    }
    if(i < n)
    {
        waiting_player->removePiece(i);
    }
}
