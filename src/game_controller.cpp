
#include "game_controller.hpp"
#include "pawn.hpp"
#include "bishop.hpp"
#include "queen.hpp"
#include "rook.hpp"
#include "knight.hpp"
#include <cstring>

/*----------------------Constructeurs / Destructeurs----------------------*/
GameController::GameController(): current_player{std::make_shared<Player>(false)} ,
    waiting_player{std::make_shared<Player>(true)} ,
    piece_chosen{nullptr} ,
    waiting_promotion{false}
{
    cell_chosen.setXY(-1,-1);
}

GameController::~GameController()
{
    
}

/*------------------------Surcharge d'Opérateurs--------------------------*/
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

/*--------------------------------Getters---------------------------------*/
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
    return cell_chosen;
}

/*---------------------------Tours Des Joueurs----------------------------*/
void GameController::switchTurn()
{
    std::swap(current_player,waiting_player);
}

bool GameController::whiteTurn()
{
    return current_player->isWhite();
}

bool GameController::blackTurn()
{
    return current_player->isBlack();
}

/*-----------------------------Pièce Choisie------------------------------*/
bool GameController::isNull(){
    return piece_chosen==nullptr;
}

bool GameController::isChosen()
{
    return piece_chosen!=nullptr;
}

void GameController::choosePiece(Coordinates c)
{
    this->piece_chosen=current_player->getPiece(c);
    if(piece_chosen != nullptr)
        this->cell_chosen =piece_chosen->getCoordinates();
}

void GameController::choosePiece(int i)
{
    this->piece_chosen=current_player->getPiece(i);
    if(piece_chosen != nullptr)
        this->cell_chosen = piece_chosen->getCoordinates();
}

void GameController::choosePiece(std::shared_ptr<Piece> p)
{
    this->piece_chosen=p;
    if(this->piece_chosen != nullptr)
        this->cell_chosen = piece_chosen->getCoordinates();
}

void GameController::unChoosePiece()
{
    this->piece_chosen=nullptr;
    cell_chosen.setXY(-1,-1);
}

std::vector<Coordinates> GameController::movesOfPieceChosen()
{
    std::vector<Coordinates> v;
    v.reserve(16);
    std::shared_ptr<Piece> p=current_player->getPiece(cell_chosen);
    Coordinates to;
    if(isChosen())
    {
        int i; 
        int j;
        for(i = 0 ; i < 8 ; ++i)
        {
            for(j = 0 ; j < 8 ; ++j)
            {
                to.setXY(j,i);
                if(isLegalMove(cell_chosen, to))
                {
                    v.push_back(to);
                }
            }
        }
    }
    return v;
}   

void GameController::movesOfPieceChosen(std::vector<Coordinates> &v)
{
    v.clear();
    std::shared_ptr<Piece> p=current_player->getPiece(cell_chosen);
    std::vector<Coordinates>& list_move=p->getVectMove();
    Coordinates to;
    if(isChosen())
    {
        size_t i;
        size_t i_max=list_move.size();

        for(i=0;i<i_max;i++)
        {
            to=cell_chosen+list_move[i];
            if(isLegalMove(cell_chosen,to))
            {
                v.push_back(to);
            }
        }
    }
}  

/*------------------------------Déplacements------------------------------*/

/*-----------------------Vérifications & Détections-----------------------*/
bool GameController::isEmpty(Coordinates c)
{
    return !pieceDectection(c);
}

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
            return true;
        }
        i += step_y;
        j += step_x;
    }
    return false;
}


/*----------------------------Règles Spéciales----------------------------*/






int GameController::countLegalMovesOfPiece(std::shared_ptr<Piece> p)
{
    int moves=0;
    Coordinates p_coord=p->getCoordinates();
    int i,j;
    for(i=0;i<8;i++)
    {
        for(j=0;j<8;j++)
        {
            Coordinates to(j,i);
            if(isLegalMove(p_coord,to))
            {
                moves++;
            }
        }
    }
    return moves;
}

bool GameController::isPawnPromoted(Coordinates c, bool color)
{
    std::shared_ptr<Piece> p ;
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

bool GameController::promotionPending()
{
    return waiting_promotion;
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


/*------------------------------Déplacements------------------------------*/
bool GameController::isLegalMove(Coordinates from, Coordinates to)
{
    if(!from.onBoard() || !to.onBoard()) return false;  

    if(from == to) return false;

    std::shared_ptr<Piece> p = current_player->getPiece(from);

    if(p == nullptr) return false;

    if(pieceInBetween(from,to)) return false;

    if(isMoveRock(from,to)){
        if(!canRock(from,to)) return false;
    }

    else if(isMoveEnPassant(from,to))
    {
        if(!canEnPassant(from,to)) return false;
    }

    else{
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

    size_t i;
    std::vector<std::shared_ptr<Piece>>& wait_piece=waiting_player->getPieces();
    size_t wait_nb_piece=wait_piece.size();
    for(i=0;i<wait_nb_piece;i++)
    {
        if(wait_piece[i]->canEatPattern(c) 
        && !pieceInBetween(wait_piece[i]->getCoordinates(),c))
        {
            nb_threats++;
        }

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
    Coordinates c = current_player->getPiece(0)->getCoordinates();
    return isThreaten(c);
}


bool GameController::isKingCheckedAfterMove(Coordinates from, Coordinates to)
{
    if(!from.onBoard() || !to.onBoard()) return false;

    std::shared_ptr<Piece> p = current_player->getPiece(from);
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
        std::shared_ptr<Piece> enemy = waiting_player->getPiece(to);
        
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
    std::shared_ptr<Piece> p;
    size_t piece_i = 0;
    size_t n = current_player->nbOfPieces();

    while(piece_i < n) //On vérifie pour chaque pièce si elle peut bouger à tous les emplacements du plateau
    {
        p = current_player->getPiece(piece_i);

        Coordinates c_piece = p->getCoordinates();        
        for(int x = 0 ; x < 8 ; x++)
        {
            for(int y = 0 ; y < 8 ; ++y)
            {
                Coordinates tmp_to(x,y);
                if(isLegalMove(c_piece,tmp_to)) return false;
            }
        }
        piece_i++;
    }

    return true;
}

bool GameController::movePiece(Coordinates from, Coordinates to)
{
    if(isLegalMove(from,to)){
        MoveHistory unitMove(from,to);
        std::shared_ptr<Piece> p = current_player->getPiece(from);
        if(p != nullptr)
        {
            if(pieceEnemyDetection(to)){
                std::shared_ptr<Piece> p_mangee = waiting_player->getPiece(to);
                unitMove.eatenPiece=p_mangee;
                eatPiece(p_mangee);
            }
            //Déplacer la pièce

            if(isMoveRock(from,to))
            {
                unitMove.rookRockFrom=rock(to);
            }
            else if(isMoveEnPassant(from,to)) 
            {
                std::shared_ptr<Piece> p_mangee = waiting_player->getPiece(moves.top().to);
                unitMove.enPassantInfo.first=p_mangee;
                unitMove.enPassantInfo.second=p_mangee->getCoordinates();
                enPassant(from,to);
            }
            else p->moveTo(to.getX(),to.getY());
            p->incrementNbOfMoves();
            unChoosePiece();

            //Màj si Pion promu
            if(isPawnPromoted(to,current_player->isBlack()))
            {
                unitMove.promotedPiece=p;
                waiting_promotion = true;
            }
            moves.push(unitMove);

            return true;
        }
    }
    return false;
}

void GameController::unMove()
{
    if(!moves.empty())
    {
        this->switchTurn();
        MoveHistory h=moves.top();
        moves.pop();

        if(h.promotedPiece!=nullptr)
        {
            current_player->removePiece(h.to);
            h.promotedPiece->moveTo(h.from);
            current_player->addPiece(h.promotedPiece);
        }
        else{
            std::shared_ptr<Piece> p = current_player->getPiece(h.to);
            p->moveTo(h.from); 
            p->decrementNbOfMoves();
        }

        if(h.eatenPiece!=nullptr)
        {
            h.eatenPiece->moveTo(h.to);
            waiting_player->addPiece(h.eatenPiece);
        }

        if(h.enPassantInfo.first!=nullptr)
        {
            Coordinates c = h.enPassantInfo.second;
            h.enPassantInfo.first->moveTo(c);
            waiting_player->addPiece(h.enPassantInfo.first);
        }

        if(h.rookRockFrom!=Coordinates(-1,-1))
        {
            Coordinates c(h.rookRockFrom.getX()==7 ? 5:3,current_player->isWhite() ? 7:0);
            std::shared_ptr<Piece> p = current_player->getPiece(c);
            p->moveTo(h.rookRockFrom);
            
        }

        
        

    }
}

void GameController::eatPiece(std::shared_ptr<Piece> p)
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

void GameController::promoteTo(std::shared_ptr<Piece> p, PieceType t)
{
    if(waiting_promotion){
        if(t == PieceType::Bishop)
        {
            bool color = current_player->isBlack();
            Coordinates c = p->getCoordinates();
            current_player->removePiece(c);

            std::shared_ptr<Bishop> b = std::make_shared<Bishop>(color, c);
            current_player->addPiece(std::move(b));
        }
        else if(t == PieceType::Knight)
        {
            bool color = current_player->isBlack();
            Coordinates c = p->getCoordinates();
            current_player->removePiece(c);

            std::shared_ptr<Knight> k = std::make_shared<Knight>(color, c);
            current_player->addPiece(std::move(k));
        }
        else if(t == PieceType::Rook)
        {
            bool color = current_player->isBlack();
            Coordinates c = p->getCoordinates();
            current_player->removePiece(c);

            std::shared_ptr<Rook> r = std::make_shared<Rook>(color, c);
            current_player->addPiece(std::move(r));       
        }else if(t == PieceType::Queen)
        {
            bool color = current_player->isBlack();
            Coordinates c = p->getCoordinates();
            current_player->removePiece(c);

            std::shared_ptr<Queen> q = std::make_shared<Queen>(color, c);
            current_player->addPiece(std::move(q));
        }
        waiting_promotion=false;
    }
}


Coordinates GameController::rock(Coordinates to)
{
    bool color = current_player->isBlack();
    std::shared_ptr<Piece> king;
    std::shared_ptr<Piece> rook;
    Coordinates c;
    if(color)
    {
        king = current_player->getPiece(4,0);
        if(4 < to.getX()) //tour droite
        {
            rook = current_player->getPiece(7,0);
            c.setXY(7,0);
            king->moveTo(6,0);
            rook->moveTo(5,0);
        }
        else //tour gauche
        {
            rook = current_player->getPiece(0,0);
            c.setXY(0,0);
            king->moveTo(2,0);
            rook->moveTo(3,0);
        }

    }
    else
    {
        king = current_player->getPiece(4,7);
        if(4 < to.getX()) //tour droite
        {
            rook = current_player->getPiece(7,7);
            c.setXY(7,7);
            king->moveTo(6,7);
            rook->moveTo(5,7);
        }
        else   //tour gauche
        {
            rook = current_player->getPiece(0,7);
            c.setXY(0,7);
            king->moveTo(2,7);
            rook->moveTo(3,7);
        }
    }
    return c;
}


bool GameController::isMoveRock(Coordinates from, Coordinates to)
{
    std::shared_ptr<Piece> p = current_player->getPiece(from);
    if(!p) return false;
    if(p->getType() == PieceType::King)
    {
        if(from.getX() == 4){
            bool color = current_player->isBlack();
            if( (from.getY() == 0 && color) || 
            (from.getY() == 7 && !color) ){
                if(from.distX(to) == 2 && from.distY(to) == 0)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

bool GameController::canRock(Coordinates from, Coordinates to)
{
    bool color = current_player->isBlack();
    std::shared_ptr<Piece> king = current_player->getPiece(from);
    if(!king) return false;

    std::shared_ptr<Piece> rook;
    if(from.getX() < to.getX()) //tour droite
    {
        if(color) rook = current_player->getPiece(7,0);
        else rook = current_player->getPiece(7,7);
    }
    else
    {
        if(color) rook = current_player->getPiece(0,0);
        else rook = current_player->getPiece(0,7);
    }

    if(!rook) return false;

    if(king->howManyMoves() == 0 && rook->howManyMoves() == 0)
    {
        int x=from.getX()-to.getX();
        if(x<0) x*=-1;

        Coordinates c_intermediaire(from.getX()-to.getX(),from.getY());
        if(!isThreaten(from) && !isThreaten(c_intermediaire))
        {
            return true;
        }
    }
    return false;
}

void GameController::enPassant(Coordinates from, Coordinates to)
{
    bool color = current_player->isBlack();
    std::shared_ptr<Piece> ally_pawn = current_player->getPiece(from);
    
    Coordinates c_enemy;
    if(color) c_enemy.setXY(to.getX(),from.getY());
    else c_enemy.setXY(to.getX(),from.getY());
    
    ally_pawn->moveTo(to);
    waiting_player->removePiece(c_enemy);
}

bool GameController::isMoveEnPassant(Coordinates from, Coordinates to)
{
    bool color = current_player->isBlack();
    std::shared_ptr<Piece> p = current_player->getPiece(from);
    if(p->getType() == PieceType::Pawn)
    {
        if(from.distX(to) == 1 && from.distY(to) == 1)
        {
            Coordinates c_enemy;
            if(color) c_enemy.setXY(to.getX(),from.getY());
            else c_enemy.setXY(to.getX(),from.getY());
            
            std::shared_ptr<Piece> enemy = waiting_player->getPiece(c_enemy);
            if(enemy && enemy->getType() == PieceType::Pawn) return true;
        }
    }
    return false;
}

bool GameController::canEnPassant(Coordinates from, Coordinates to)
{
    bool color = current_player->isBlack();
    std::shared_ptr<Piece> p = current_player->getPiece(from);
    std::shared_ptr <Piece> enemy;

    Coordinates c_enemy;
    if(color) c_enemy.setXY(to.getX(),to.getY()-1);
    else c_enemy.setXY(to.getX(),to.getY()+1);

    enemy = waiting_player->getPiece(c_enemy);
    if(enemy && enemy->howManyMoves() == 1)
    {
        if(!moves.empty()){
            MoveHistory last = moves.top();
            Coordinates cell_necessary;
            if(color) cell_necessary.setXY(c_enemy.getX(),c_enemy.getY()+2);
            else cell_necessary.setXY(c_enemy.getX(),c_enemy.getY()-2);

            if(cell_necessary == last.from && c_enemy == last.to) return true;
        }
    }

    return false;
}