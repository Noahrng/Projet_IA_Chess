#include "player.hpp"
#include "pawn.hpp"
#include "bishop.hpp"
#include "knight.hpp" 
#include "rook.hpp"
#include "queen.hpp"
#include "king.hpp"

Player::Player(bool color):color{color},sum_point{39.0}
{
    //Création de chaque pieces
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
}

std::shared_ptr<Piece> Player::getPiece(int x, int y)
{
    Coordinates c(x,y);
    return getPiece(c);
}

std::shared_ptr<Piece> Player::getPiece(Coordinates c)
{
    if(!c.onBoard()) return nullptr;
    size_t  i = 0;
    size_t  i_max=pieces.size();
    while(i < i_max && pieces[i]->getCoordinates()!=c){
        i++;
    }
    if(i < i_max){
        return pieces[i];
    }
    return nullptr;
}
std::shared_ptr<Piece> Player::getPiece(size_t i)
{
    if(i < pieces.size())
    {
        return pieces[i];
    }
    return nullptr;
}

double Player::getPoint()
{
    return sum_point;
}

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

bool Player::isPiece(std::shared_ptr<Piece> p, size_t i)
{
    return p == pieces[i];
}

bool Player::isWhite()
{
    return !color;
}

bool Player::isBlack()
{
    return color;
}

size_t Player::nbOfPieces()
{
    return pieces.size();
}

void Player::addPiece(std::shared_ptr<Piece> p)
{
    sum_point+=p->getValue();
    pieces.push_back(std::move(p));
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
        sum_point-=pieces[i]->getValue();
        pieces.erase(pieces.begin()+i);
        
    }
}

void Player::removePiece(size_t i){
    if(i < nbOfPieces()){
        pieces[i]->moveTo(Coordinates(-1,-1));
        sum_point-=pieces[i]->getValue();
        pieces.erase(pieces.begin()+i);
    }
}

void Player::removePiece(std::shared_ptr<Piece> p){
    size_t i = 0;
    size_t n = nbOfPieces();

    while(i < n)
    {
        if(pieces[i] == p)
        {
            removePiece(i);
        }
        i++;    
    }
}