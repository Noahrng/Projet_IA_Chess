
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
    hashHistory.push_back(computeKey());
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
Coordinates GameController::getCoordsPieceChosen() const
{
    return cell_chosen;
}

std::pair<Coordinates,Coordinates> GameController::getLastMove() const
{
    std::pair<Coordinates,Coordinates> lastMove={Coordinates(-1,-1),Coordinates(-1,-1)};
    if(!moves.empty())
    {
        MoveHistory h=moves.back();
        lastMove.first=h.from;
        lastMove.second=h.to;
    }
    return lastMove;
}

/*---------------------------Tours Des Joueurs----------------------------*/
void GameController::switchTurn()
{
    std::swap(current_player,waiting_player);
}

bool GameController::whiteTurn() const
{
    return current_player->isWhite();
}

bool GameController::blackTurn() const
{
    return current_player->isBlack();
}

/*Calcul de position*/
uint8_t GameController::encodePiece(PieceType type, bool isBlack) const
{
    int base = isBlack ? 6 : 0;
    return base + static_cast<int>(type) + 1;
}

void GameController::setCase(PositionKey& key, int x, int y, uint8_t val) const
{
    int index = y * 8 + x;
    int word  = index / 16;
    int bit   = (index % 16) * 4;
    key.data[word] |= ((uint64_t)val << bit);
}

PositionKey GameController::computeKey() const
{
    PositionKey key;
    key.data.fill(0);
    key.white_turn = current_player->isWhite();

    for(size_t i = 0; i < current_player->nbOfPieces(); i++)
    {
        auto p = current_player->getPiece(i);
        if(!p->getCoordinates().onBoard()) continue;
        setCase(key,
                p->getCoordinates().getX(),
                p->getCoordinates().getY(),
                encodePiece(p->getType(), current_player->isBlack()));
    }

    for(size_t i = 0; i < waiting_player->nbOfPieces(); i++)
    {
        auto p = waiting_player->getPiece(i);
        if(!p->getCoordinates().onBoard()) continue;
        setCase(key,
                p->getCoordinates().getX(),
                p->getCoordinates().getY(),
                encodePiece(p->getType(), waiting_player->isBlack()));
    }

    return key;
}

/*-----------------------------Pièce Choisie------------------------------*/
bool GameController::isNull() const
{
    return piece_chosen==nullptr;
}

bool GameController::isChosen() const
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

int GameController::movesOfPieceChosen(Coordinates *v)
{
    int nbmove=0;
    std::shared_ptr<Piece> p=current_player->getPiece(cell_chosen);
    std::vector<Coordinates>& list_move=p->getVectMove();
    Coordinates to;
    if(isChosen())
    {
        switch (p->getType())
        {
            case PieceType::Bishop:
            {
                int dx[]={1,1,-1,-1};
                int dy[]={1,-1,1,-1};
                for(int d = 0; d < 4; d++)
                {
                    to = cell_chosen;
                    to.setXY(to.getX()+dx[d], to.getY()+dy[d]);
                    while(to.onBoard())
                    {
                        if(isLegalMove(cell_chosen, to))
                            v[nbmove++]=to;
                        if(pieceDectection(to)) break;
                        to.setXY(to.getX()+dx[d], to.getY()+dy[d]);
                    }
                }
                break;
            }

            case PieceType::Rook:
            {
                int dx[] = {1, -1, 0, 0};
                int dy[] = {0, 0, 1, -1};
                for(int d = 0; d < 4; d++)
                {
                    to = cell_chosen;
                    to.setXY(to.getX()+dx[d], to.getY()+dy[d]);
                    while(to.onBoard())
                    {
                        if(isLegalMove(cell_chosen, to))
                            v[nbmove++]=to;
                        if(pieceDectection(to)) break; // ← arrêt si pièce rencontrée
                        to.setXY(to.getX()+dx[d], to.getY()+dy[d]);
                    }
                }
                break;
            }

            case PieceType::Queen:
            {
                int dx[] = {1, 1, -1, -1, 1, -1, 0, 0};
                int dy[] = {1, -1, 1, -1, 0, 0, 1, -1};
                for(int d = 0; d < 8; d++)
                {
                    to = cell_chosen;
                    to.setXY(to.getX()+dx[d], to.getY()+dy[d]);
                    while(to.onBoard())
                    {
                        if(isLegalMove(cell_chosen, to))
                            v[nbmove++]=to;
                        if(pieceDectection(to)) break; // ← arrêt si pièce rencontrée
                        to.setXY(to.getX()+dx[d], to.getY()+dy[d]);
                    }
                }
                break;
            }
            
            default:
            {
                for(auto it = list_move.begin(); it != list_move.end(); ++it)
                {
                    to = cell_chosen + *it; // ← cell_chosen + *it, pas juste *it
                    if(isLegalMove(cell_chosen, to))
                        v[nbmove++]=to;
                }
                break;
            }
            
        }
    }
    return nbmove;
}  

/*------------------------------Déplacements------------------------------*/
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

bool GameController::movePiece(Coordinates from, Coordinates to,bool autoPromote)
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
            else if(unitMove.eatenPiece==nullptr && isMoveEnPassant(from,to)) 
            {
                bool color = current_player->isBlack();
                Coordinates c_enemy;
                if(color) c_enemy.setXY(to.getX(),from.getY());
                else c_enemy.setXY(to.getX(),from.getY());

                std::shared_ptr<Piece> p_mangee = waiting_player->getPiece(c_enemy);
                if(p_mangee==nullptr) return false;

                unitMove.enPassantInfo.first=p_mangee;
                unitMove.enPassantInfo.second=p_mangee->getCoordinates();
                enPassant(from,to);
            }
            else
            {
                p->moveTo(to.getX(),to.getY());
            }
            p->incrementNbOfMoves();
            unChoosePiece();

            //Màj si Pion promu
            if(isPawnPromoted(to,current_player->isBlack()))
            {
                unitMove.promotedPiece=p;
                waiting_promotion=true;

                if(autoPromote)
                    promoteTo(p,PieceType::Queen);      
            }
            moves.push_back(unitMove);
            hashHistory.push_back(computeKey());

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
        MoveHistory h=moves.back();
        moves.pop_back();

        if(h.promotedPiece!=nullptr)
        {
            current_player->removePiece(h.to);
            h.promotedPiece->moveTo(h.from);
            h.promotedPiece->decrementNbOfMoves();
            current_player->addPiece(h.promotedPiece);

            waiting_promotion = false;
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

        
        if(!hashHistory.empty())
            hashHistory.pop_back();

    }
}


/*-----------------------Vérifications & Détections-----------------------*/
bool GameController::isEmpty(Coordinates c) const
{
    return !pieceDectection(c);
}

bool GameController::pieceInBetween(Coordinates from, Coordinates to) const
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

bool GameController::pieceAllyDetection(Coordinates c) const
{
    return current_player->getPiece(c)!=nullptr;
}

bool GameController::pieceEnemyDetection(Coordinates c) const
{
    return waiting_player->getPiece(c)!=nullptr;
}

bool GameController::pieceDectection(Coordinates c) const
{
    return this->pieceAllyDetection(c) || this->pieceEnemyDetection(c);
}

bool GameController::isLegalMove(Coordinates from, Coordinates to)
{
    std::shared_ptr<Piece> p = current_player->getPiece(from);
    
    if(!from.onBoard() || !to.onBoard()) return false;  

    if(from == to) return false;

    if(p == nullptr) return false;

    if(p->getType() == PieceType::Bishop ||
        p->getType() == PieceType::Rook ||
        p->getType() == PieceType::Queen ||
        p->getType() == PieceType::King ||
        p->getType() == PieceType::Pawn)
    {
        if(pieceInBetween(from,to)) return false;
    }
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

int GameController::countLegalMovesOfPiece(std::shared_ptr<Piece> p)
{
    int moves=0;
    std::vector<Coordinates>& list_move=p->getVectMove();
    Coordinates from=p->getCoordinates();
    Coordinates to;
    switch (p->getType())
    {
        case PieceType::Bishop:
        {
            int dx[]={1,1,-1,-1};
            int dy[]={1,-1,1,-1};
            for(int d = 0; d < 4; d++)
            {
                to = from;
                to.setXY(to.getX()+dx[d], to.getY()+dy[d]);
                while(to.onBoard())
                {
                    if(isLegalMove(from, to))
                        moves++;
                    if(pieceDectection(to)) break;
                    to.setXY(to.getX()+dx[d], to.getY()+dy[d]);
                }
            }
            break;
        }

        case PieceType::Rook:
        {
            int dx[] = {1, -1, 0, 0};
            int dy[] = {0, 0, 1, -1};
            for(int d = 0; d < 4; d++)
            {
                to = from;
                to.setXY(to.getX()+dx[d], to.getY()+dy[d]);
                while(to.onBoard())
                {
                    if(isLegalMove(from, to))
                        moves++;
                    if(pieceDectection(to)) break; // ← arrêt si pièce rencontrée
                    to.setXY(to.getX()+dx[d], to.getY()+dy[d]);
                }
            }
            break;
        }

        case PieceType::Queen:
        {
            int dx[] = {1, 1, -1, -1, 1, -1, 0, 0};
            int dy[] = {1, -1, 1, -1, 0, 0, 1, -1};
            for(int d = 0; d < 8; d++)
            {
                to = from;
                to.setXY(to.getX()+dx[d], to.getY()+dy[d]);
                while(to.onBoard())
                {
                    if(isLegalMove(from, to))
                        moves++;
                    if(pieceDectection(to)) break; // ← arrêt si pièce rencontrée
                    to.setXY(to.getX()+dx[d], to.getY()+dy[d]);
                }
            }
            break;
        }
            
        default:
        {
            for(auto it = list_move.begin(); it != list_move.end(); ++it)
            {
                to = from + *it; // ← cell_chosen + *it, pas juste *it
                if(isLegalMove(from, to))
                    moves++;
            }
            break;
        }
    }
    
    return moves;
}

int GameController::isThreaten(Coordinates c) const
    /* 
    Vérifie si une case aux coordonnées c est menacée ou non par une pièce 
    et renvoie le nombre de pièces qui la menace
    */    
{
    if(!c.onBoard()) return 0;
    
    int nb_threats = 0;

    size_t i = 0;
    while(i < waiting_player->nbOfPieces())
    {
        std::shared_ptr<Piece> p = waiting_player->getPiece(i);
        if(p->canEatPattern(c) && 
        !pieceInBetween(p->getCoordinates(),c)) 
        {
            nb_threats++;
        }
        i++;
    }
    return nb_threats;
}

int GameController::isChecked() const
/* 
    Vérifie si un joueur est en échec ou pas et renvoie le nombre de pièces qui le met en échec.
*/
{
    std::shared_ptr<Piece> king = current_player->getKing();
    Coordinates c = king->getCoordinates();
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

    bool isEP = (p->getType() == PieceType::Pawn)
             && (from.distX(to) == 1)
             && (from.distY(to) == 1)
             && isEmpty(to);  // ← détection manuelle, sans appeler isMoveEnPassant

    Coordinates epCoords(-1,-1);
    std::shared_ptr<Piece> epEnemy = nullptr;

    if(isEP)
    {
        epCoords.setXY(to.getX(), from.getY());  // le pion ennemi est sur la même rangée que from
        epEnemy = waiting_player->getPiece(epCoords);
    }

    
    p->moveTo(to);  // On simule le coup
    
    //Si on mange une pièce, on la sauvegarde aussi
    if(pieceEnemyDetection(to))
    {
        std::shared_ptr<Piece> enemy = waiting_player->getPiece(to);
        Coordinates saved_enemy_c = enemy->getCoordinates();
        waiting_player->removePiece(enemy);


        checked = isChecked();

        enemy->moveTo(saved_enemy_c);
        waiting_player->addPiece(enemy);
    }
    else if(isEP && epEnemy != nullptr)
    {
        waiting_player->removePiece(epEnemy);
        checked = isChecked();
        epEnemy->moveTo(epCoords);
        waiting_player->addPiece(epEnemy);
    }
    else
    {
        checked = isChecked();
    }
    p->moveTo(saved_x,saved_y);
    return checked;
}

bool GameController::isRepeat() const
{
    if(hashHistory.size() < 5) return false;

    const PositionKey& current = hashHistory.back();
    int count = 0;

    for(size_t i = 0; i < hashHistory.size(); i++)
    {
        if(hashHistory[i] == current)
            count++;
        if(count >= 3)
            return true;
    }
    return false;
}

bool GameController::isDraw()
{
    if(isRepeat()) return true;
    //Matériel insuffisant :
    size_t n1 = current_player->nbOfPieces();
    size_t n2 = waiting_player->nbOfPieces();

    //Cas 1: Roi contre Roi
    if(n1 == 1 && n2 == 1) 
    //automatiquement un roi contre un roi
    {
        return true;
    }

    //Cas 2: Roi contre Fou/Cavalier (ou Fou/Cavalier contre Roi)  
    if(n1 == 1 && n2 == 2)
    {
        std::shared_ptr<Piece> p;
        for(size_t i = 0 ; i  < n2 ; ++i) 
        {
            p = waiting_player->getPiece(i);
            if(p->getType() == PieceType::Bishop || p->getType() == PieceType::Knight)
            {
                return true;
            }
        }
    }
    if(n1 == 2 && n2 == 1)
    {
        std::shared_ptr<Piece> p;
        for(size_t i = 0 ; i  < n2 ; ++i) 
        {
            p = current_player->getPiece(i);
            if(p->getType() == PieceType::Bishop || p->getType() == PieceType::Knight)
            {
                return true;
            }
        }
    }

    //Cas 3 : Roi et Fou contre Roi et Fou (les deux de la même couleur)
    if(n1 == 2 && n2 == 2)
    {
        std::shared_ptr<Piece> bishop_ally = nullptr;
        std::shared_ptr<Piece> bishop_enemy = nullptr;
        
        for(size_t i  = 0 ; i < n1 ; ++i)
        {
            auto p = current_player->getPiece(i);
            if(p && p->getType() == PieceType::Bishop)
            {
                bishop_ally = p;
            }
        }

        for(size_t i  = 0 ; i < n2 ; ++i)
        {
            auto p = waiting_player->getPiece(i);
            if(p && p->getType() == PieceType::Bishop)
            {
                bishop_enemy = p;
            }
        }

        if(bishop_ally && bishop_enemy)
        {
            Coordinates ally_coords = bishop_ally->getCoordinates();
            Coordinates enemy_coords = bishop_enemy->getCoordinates();
            if( (ally_coords.getX() + ally_coords.getY()) % 2 == (enemy_coords.getX() + enemy_coords.getY()) % 2)
            //On vérifie si les deux fous sont sur les cases de même couleur
            //Case blanche  : x + y est pair
            //Case noire    : x + y est impair
            {
                return true;
            }
        }
    }

    //Pat:
    if(isPat()) return true;


    return false;
}

bool GameController::isPat()
{
    if(!isChecked()){
        size_t n = current_player->nbOfPieces();
        std::shared_ptr<Piece> p;
        for(size_t i = 0 ; i < n ; ++i)
        {
            p = current_player->getPiece(i);
            if(countLegalMovesOfPiece(p) > 0)
            {
                return false;
            }
        } 
        return true;
    }
    return false;
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
/*----------------------------Règles Spéciales----------------------------*/
bool GameController::isPawnPromoted(Coordinates c, bool color) const
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

bool GameController::promotionPending() const
{
    return waiting_promotion;
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

            std::shared_ptr<Knight> b = std::make_shared<Knight>(color, c);
            current_player->addPiece(std::move(b));
        }
        else if(t == PieceType::Rook)
        {
            bool color = current_player->isBlack();
            Coordinates c = p->getCoordinates();
            current_player->removePiece(c);

            std::shared_ptr<Rook> b = std::make_shared<Rook>(color, c);
            current_player->addPiece(std::move(b));  
        }else if(t == PieceType::Queen)
        {
            bool color = current_player->isBlack();
            Coordinates c = p->getCoordinates();
            current_player->removePiece(c);

            std::shared_ptr<Queen> b = std::make_shared<Queen>(color, c);
            current_player->addPiece(std::move(b));
        }
        waiting_promotion=false;
    }
}

bool GameController::isMoveRock(Coordinates from, Coordinates to) const
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

bool GameController::canRock(Coordinates from, Coordinates to) const
{
    bool color = current_player->isBlack();
    std::shared_ptr<Piece> king = current_player->getPiece(from);
    if(!king) return false;

    std::shared_ptr<Piece> rook;
    Coordinates rook_coords;
    if(from.getX() < to.getX()) //tour droite
    {
        if(color){
            rook = current_player->getPiece(7,0);
            rook_coords.setXY(7,0);
        }
        else{
            rook = current_player->getPiece(7,7);
            rook_coords.setXY(7,7);
        }
    }
    else
    {
        if(color) {
            rook = current_player->getPiece(0,0);
            rook_coords.setXY(0,0);
        }
        else {
            rook = current_player->getPiece(0,7);
            rook_coords.setXY(0,7);
        }
    }

    if(!rook) return false;
    if(pieceInBetween(from,rook_coords)) return false;
    if(king->howManyMoves() != 0 || rook->howManyMoves() != 0) return false;
    if(isThreaten(from)) return false;
    int direction=(to.getX()>from.getX()) ? 1 : -1;
    Coordinates c=from;
    c.setXY(c.getX()+direction,c.getY());

    while(c!=to)
    {
        if(isThreaten(c)) return false;
        c.setXY(c.getX() + direction, c.getY());
    }

    if(isThreaten(to)) return false;
    return true;
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

bool GameController::isMoveEnPassant(Coordinates from, Coordinates to) const
{
    bool color = current_player->isBlack();
    std::shared_ptr<Piece> p = current_player->getPiece(from);
    if(p->getType() == PieceType::Pawn)
    {
        if(from.distX(to) == 1 && from.distY(to) == 1 && isEmpty(to))
        {
            Coordinates c_enemy;
            if(color) c_enemy.setXY(to.getX(),from.getY());
            else c_enemy.setXY(to.getX(),from.getY());
            
            std::shared_ptr<Piece> enemy = waiting_player->getPiece(c_enemy);

            if(enemy && enemy->howManyMoves()==1 && enemy->getType() == PieceType::Pawn) return true;
        }
    }
    return false;
}

bool GameController::canEnPassant(Coordinates from, Coordinates to) const
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
            MoveHistory last = moves.back();
            Coordinates cell_necessary;
            if(color) cell_necessary.setXY(c_enemy.getX(),c_enemy.getY()+2);
            else cell_necessary.setXY(c_enemy.getX(),c_enemy.getY()-2);

            if(cell_necessary == last.from && c_enemy == last.to) return true;
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
