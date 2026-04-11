#include "player.hpp"
#include "pawn.hpp"
#include "bishop.hpp"
#include "knight.hpp" 
#include "rook.hpp"
#include "queen.hpp"
#include "king.hpp"

/*----------------------Constructeurs / Destructeurs----------------------*/
Player::Player(bool color):color{color}
{
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
            board[i][j]=nullptr;
    //Création de chaque pieces
    pieces.reserve(20);
    int i,j;
    //Pions:
    for(j = 0 ; j < 8 ; ++j){
        if(!color) i=6;
        else i=1;

        Coordinates c(j,i);
        addPiece(std::make_shared<Pawn>(color, c));
    }

    //Cavaliers
    if(!color){
        Coordinates c1(1,7);
        Coordinates c2(6,7);
        addPiece(std::make_shared<Knight>(color, c1));
        addPiece(std::make_shared<Knight>(color, c2));
    }
    else{
        Coordinates c1(1,0);
        Coordinates c2(6,0);
        addPiece(std::make_shared<Knight>(color, c1));
        addPiece(std::make_shared<Knight>(color, c2));
    }

    //Fous
    if(!color){
        Coordinates c1(2,7);
        Coordinates c2(5,7);
        addPiece(std::make_shared<Bishop>(color, c1));
        addPiece(std::make_shared<Bishop>(color, c2));
    }
    else{
        Coordinates c1(2,0);
        Coordinates c2(5,0);
        addPiece(std::make_shared<Bishop>(color, c1));
        addPiece(std::make_shared<Bishop>(color, c2));
    }
    //Tours
    if(!color){
        Coordinates c1(0,7);
        Coordinates c2(7,7);
        addPiece(std::make_shared<Rook>(color, c1));
        addPiece(std::make_shared<Rook>(color, c2));
    }
    else{
        Coordinates c1(0,0);
        Coordinates c2(7,0);
        addPiece(std::make_shared<Rook>(color, c1));
        addPiece(std::make_shared<Rook>(color, c2));
    }

    //Reine
    if(!color){
        Coordinates c(3,7);
        addPiece(std::make_shared<Queen>(color, c));
    }
    else{
        Coordinates c(3,0);
        addPiece(std::make_shared<Queen>(color, c));
    }
    //Roi
    if(!color){
        Coordinates c(4,7);
        addPiece(std::make_shared<King>(color, c));
    }
    else{
        Coordinates c(4,0);
        addPiece(std::make_shared<King>(color, c));
    }

    std::sort(pieces.begin(), pieces.end(),
        [](const std::shared_ptr<Piece> &a, const std::shared_ptr<Piece> &b)
        {
            return a->getValue() > b->getValue(); // décroissant : Dame en premier
        }
    );
}

/*------------------------Surcharge d'Opérateurs--------------------------*/
bool operator==(const Player &a,const Player &b)
{
    if(a.color!=b.color) return false;
    if(a.pieces.size()!=b.pieces.size()) return false;
    size_t i_max,j_max;

    i_max=a.pieces.size();
    for(std::size_t i=0;i<i_max;i++)
    {
        bool found=false;
        std::size_t j=0;
        j_max=b.pieces.size();
        while(j<j_max)
        {
            if(*(a.pieces[i].get()) == *(b.pieces[j].get()))
            {
                found=true;
            }
            j++;
        }
        if(!found)  
            return false;


    }
    return true;
}

bool operator!=(const Player &a,const Player &b)
{
    return !(a==b);
}


/*--------------------------------Getters---------------------------------*/
std::shared_ptr<Piece> Player::getPiece(int x, int y) const
{
    Coordinates c(x,y);
    return getPiece(c);
}

std::shared_ptr<Piece> Player::getPiece(Coordinates c) const
{
    if(!c.onBoard()) return nullptr;
    return board[c.getX()][c.getY()];
}
std::shared_ptr<Piece> Player::getPiece(size_t i) const
{
    return pieces[i];
}

std::shared_ptr<Piece> Player::getKing() const
{
    return pieces[0];
}

std::vector<std::shared_ptr<Piece>>& Player::getPieces()
{
    return pieces;
}

Piece& Player::getKingFast() const
{
    return *pieces[0].get();
}

size_t Player::nbOfPieces() const
{
    return pieces.size();
}

bool Player::isBot() const
{
    return bot;
}

/*----------------------------Setters-------------------------------------*/
void Player::setBot(bool bot)
{
    this->bot=bot;
}

void Player::updateBoard(Coordinates from,Coordinates to)
{
    board[to.getX()][to.getY()]=board[from.getX()][from.getY()];
    board[from.getX()][from.getY()]=nullptr;
}


/*--------------------------Vérification d'État---------------------------*/
bool Player::isPiece(std::shared_ptr<Piece> p, size_t i) const
{
    return p == pieces[i];
}

bool Player::isWhite() const
{
    return !color;
}

bool Player::isBlack() const
{
    return color;
}

/*----------------------------Pièces du Joueur----------------------------*/
void Player::addPiece(std::shared_ptr<Piece> p)
{
    Coordinates c=p->getCoordinates();
    pieces.push_back(p);
    size_t i=pieces.size()-1;
    while(i>0 && pieces[i]->getValue() > pieces[i-1]->getValue())
    {
        std::swap(pieces[i],pieces[i-1]);
        i--;
    }

    board[c.getX()][c.getY()]=p;
    
}

void Player::removePiece(Coordinates c){
    size_t i=0;
    size_t i_max=pieces.size();
    while(i<i_max && pieces[i]->getCoordinates()!=c){
        i++;
    }
    if(i<i_max) 
    {
        pieces[i]->moveTo(Coordinates(-1,-1));
        pieces.erase(pieces.begin()+i);
    }

    board[c.getX()][c.getY()]=nullptr;
}

void Player::removePiece(size_t i){
    if(i < nbOfPieces()){
        Coordinates c = pieces[i]->getCoordinates();
        board[c.getX()][c.getY()]=nullptr;
        pieces[i]->moveTo(Coordinates(-1,-1));
        pieces.erase(pieces.begin()+i);
    }
}
void Player::removePiece(std::shared_ptr<Piece> p){
    Coordinates c = p->getCoordinates();
    removePiece(c);
}