#include "game_controller.hpp"
#include "pawn.hpp"
#include "bishop.hpp"
#include "queen.hpp"
#include "rook.hpp"
#include "knight.hpp"
#include <cstring>

GameController::GameController()
{
    current_player = new Player(false);
    waiting_player = new Player(true);
    piece_chosen = nullptr;
    cell_chosen.setXY(-1,-1);
}

GameController::~GameController()
{
    std::cout<<"[DEBUG] GameController destructor\n";
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
    std::cin>>entry;
    return entry;
} 

bool GameController::moveCancelled(std::string s)
{
    return (s == "cancel");
}


void GameController::switchTurn()
{
    auto tmp = current_player;
    current_player = waiting_player;
    waiting_player = tmp;
}

Player& GameController::getCurrentPlayer()
{
    return *current_player;
}
Player& GameController::getWaitingPlayer()
{
    return *waiting_player;
}
Coordinates GameController::getCoordsPieceChosen()
{
    return piece_chosen->getCoordinates();
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

bool GameController::whiteTurn()
{
    return current_player->isWhite();
}

bool GameController::blackTurn()
{
    return current_player->isBlack();
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

void GameController::choosePiece(Coordinates c)
{
    this->piece_chosen=current_player->getPiece(c);
    if(piece_chosen != nullptr)
        this->cell_chosen = current_player->getPiece(c)->getCoordinates();
}

void GameController::unChoosePiece()
{
    if(piece_chosen!=nullptr)
    {
        this->piece_chosen=nullptr;
        cell_chosen.setXY(-1,-1);
    }
}

bool GameController::isChosen()
{
    return piece_chosen!=nullptr;
}

std::vector<Coordinates> GameController::movesOfPieceChosen()
{
    std::vector<Coordinates> v;
    if(isChosen())
    {
        int i; 
        int j;
        for(i = 0 ; i < 8 ; ++i)
        {
            for(j = 0 ; j < 8 ; ++j)
            {
                Coordinates to(j,i);
                if(piece_chosen->canMovePattern(to) && isEmpty(to) 
                    && !pieceInBetween(cell_chosen,to))
                {
                    v.push_back(to);
                }
                else if(pieceEnemyDetection(to) && piece_chosen->canEatPattern(to) 
                    && !pieceInBetween(cell_chosen,to))
                {
                    v.push_back(to);
                }
            }
        }
    }
    return v;
}   

bool GameController::isPromoted(Coordinates c, bool color)
{
    Piece * p ;
    if( (current_player->isWhite() && color == 0) || 
     (current_player->isBlack() && color == 1)) 
        p = current_player->getPiece(c);
    else p = waiting_player->getPiece(c);

    if(p)
    {
        if(p->getType() == PieceType::Pawn)
        {
            if(!color && p->getCoordinates().getY() == 0) return true;
            if(color && p->getCoordinates().getY() == 7) return true;
        }
    }

    return false;
}

bool GameController::isEmpty(Coordinates c)
{
    return !pieceDectection(c);
}

bool GameController::pieceAllyDetection(Coordinates c)
{
    return current_player->getPiece(c)!=nullptr;
}
bool GameController::pieceEnemyDetection(Coordinates c)
{
    return waiting_player->getPiece(c)!=nullptr;
}
bool GameController::pieceDectection(Coordinates c)
{
    return this->pieceAllyDetection(c) || this->pieceEnemyDetection(c);
}

bool GameController::isLegalMove(Coordinates from, Coordinates to)
{

    Piece * p = current_player->getPiece(from);
    
    if(!from.onBoard() || !to.onBoard()) return false;  

    if(p == nullptr) return false;

    if(pieceInBetween(from,to)) return false;

    if(isEmpty(to))
    {
        if(!p->canMovePattern(to)) return false;
    }
    else if(pieceEnemyDetection(to))
    {
        if(!p->canEatPattern(to)) return false;
    }
    else
    {
        return false;
    }

    if(isKingCheckedAfterMove(from,to))
    {
        return false;
    }

    return true;
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
        if(p->canEatPattern(c) && 
        !pieceInBetween(p->getCoordinates(),c)) 
        {
            nb_threats++;
        }
        i++;
    }
    return nb_threats;
}

int GameController::isChecked()
/* 
    Vérifie si un joueur est en échec ou pas et renvoie le nombre de pièces qui le met en échec.
*/
{
    size_t n = current_player->nbOfPieces();
    if(n == 0)
    {
        return 0;
    }

    size_t i = 0;
    Piece * king = nullptr;
    bool is_king = false;
    
    while(i < n && !is_king)
    {
        king = current_player->getPiece(i);
        is_king = king->getType() == PieceType::King;
        i++;
    }

    if(!is_king)
    {
        return 0;
    }

    Coordinates c = king->getCoordinates();
    return isThreaten(c);
}


bool GameController::isKingCheckedAfterMove(Coordinates from, Coordinates to)
{
    if(!from.onBoard() || !to.onBoard()) return false;

    Piece *p = current_player->getPiece(from);
    if(p == nullptr) return false;

    bool checked;
    int saved_x, saved_y;

    //On sauvegarde les coordonnées de la pièce
    saved_x = from.getX();
    saved_y = from.getY();

    p->moveTo(to);  // On simule le coup
    
    //Si on mange une pièce, on la sauvegarde aussi
    if(pieceEnemyDetection(to))
    {
        int saved_enemy_x, saved_enemy_y;
        Piece* enemy = waiting_player->getPiece(to);
        
        //on sauvegarde les coordonnées de la pièce ennemie
        saved_enemy_x = enemy->getCoordinates().getX();
        saved_enemy_y = enemy->getCoordinates().getY();

        enemy->moveTo(-1,-1); //En dehors du board pour pas qu'on la prenne en compte

        checked = isChecked();
        enemy->moveTo(saved_enemy_x,saved_enemy_y);
    }
    else
    {
        checked = isChecked();
    }
    p->moveTo(saved_x,saved_y);
    return checked;
}

bool GameController::isCheckmate()
/* 
    Vérifie si current player est en échec et mat
*/
{
    if(!isChecked())
    {
        return false;
    }
    std::cout << "[DEBUG] appel à checkmate\n";
    Piece * p;
    size_t piece_i = 0;
    size_t n = current_player->nbOfPieces();

    int x, y;
    while(piece_i < n) //On vérifie pour chaque pièce si elle peut bouger à tous les emplacements du plateau
    {
        p = current_player->getPiece(piece_i);

        Coordinates c_piece = p->getCoordinates();

        

        x=0;
        while(x < 8)
        {
            std::cout << "[DEBUG] Blocus en boucle x\n";
            y=0;
            while(y < 8)
            {
                std::cout << "[DEBUG] Blocus en boucle y\n";
                Coordinates tmp_to(x,y);
                if(isLegalMove(c_piece,tmp_to)) return false;
                y++;
            }
            x++;
        }
        piece_i++;
        std::cout << "piece_i : " << piece_i << ", x: " << x << ", y:" << y << "\n";
    }
    std::cout << "[DEBUG isCheckmate()] Echec et mat (sauf (8, 8)) en ()" << x << ", " << y << ")\n";

    return true;
}

bool GameController::movePiece(Coordinates from, Coordinates to)
{
    if(isLegalMove(from,to)){
        Piece * p = current_player->getPiece(from);
        if(p != nullptr)
        {
            if(pieceEnemyDetection(to)){
                Piece * p_mangee = waiting_player->getPiece(to);
                eatPiece(p_mangee);
            }
            //Déplacer la pièce

            p->moveTo(to.getX(),to.getY());
            unChoosePiece();
            //Màj si Pion promu
            if(isPromoted(to,current_player->isBlack()))
            {
                promoteTo(p,PieceType::Knight);
            }

            return true;
        }
    }
    return false;
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

void GameController::promoteTo(Piece * p, PieceType t)
{
    if(t == PieceType::Bishop)
    {
        bool color = current_player->isBlack();
        Coordinates c = p->getCoordinates();
        current_player->removePiece(c);

        std::unique_ptr<Bishop> b = std::make_unique<Bishop>(color, c);
        current_player->addPiece(std::move(b));
    }
    else if(t == PieceType::Knight)
    {
        bool color = current_player->isBlack();
        Coordinates c = p->getCoordinates();
        current_player->removePiece(c);

        std::unique_ptr<Knight> k = std::make_unique<Knight>(color, c);
        current_player->addPiece(std::move(k));
    }
    else if(t == PieceType::Rook)
    {
        bool color = current_player->isBlack();
        Coordinates c = p->getCoordinates();
        current_player->removePiece(c);

        std::unique_ptr<Rook> r = std::make_unique<Rook>(color, c);
        current_player->addPiece(std::move(r));        
    }else if(t == PieceType::Queen)
    {
        bool color = current_player->isBlack();
        Coordinates c = p->getCoordinates();
        current_player->removePiece(c);

        std::unique_ptr<Queen> q = std::make_unique<Queen>(color, c);
        current_player->addPiece(std::move(q));
        
    }
}