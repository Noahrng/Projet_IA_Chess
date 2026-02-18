#include "player.hpp"
#include "pawn.hpp"
#include "bishop.hpp"
#include "knight.hpp" 
#include "rook.hpp"
#include "queen.hpp"
#include "king.hpp"

Player::Player(bool color):color{color}
{
    //Création de chaque pieces
    std::cout<<"constructeur" <<color << "\n";
    int i,j;
    //Pions:
    for(j = 0 ; j < 8 ; ++j){
        if(!color) i=6;
        else i=1;

        Coordinates c(j,i);
        pieces.push_back(std::make_unique<Pawn>(color, c));
    }

    //Cavaliers
    if(!color){
        Coordinates c1(1,7);
        Coordinates c2(6,7);
        pieces.push_back(std::make_unique<Knight>(color, c1));
        pieces.push_back(std::make_unique<Knight>(color, c2));
    }
    else{
        Coordinates c1(1,0);
        Coordinates c2(6,0);
        pieces.push_back(std::make_unique<Knight>(color, c1));
        pieces.push_back(std::make_unique<Knight>(color, c2));
    }

    //Fous
    if(!color){
        Coordinates c1(2,7);
        Coordinates c2(5,7);
        pieces.push_back(std::make_unique<Bishop>(color, c1));
        pieces.push_back(std::make_unique<Bishop>(color, c2));
    }
    else{
        Coordinates c1(2,0);
        Coordinates c2(5,0);
        pieces.push_back(std::make_unique<Bishop>(color, c1));
        pieces.push_back(std::make_unique<Bishop>(color, c2));
    }
    //Tours
    if(!color){
        Coordinates c1(0,7);
        Coordinates c2(7,7);
        pieces.push_back(std::make_unique<Rook>(color, c1));
        pieces.push_back(std::make_unique<Rook>(color, c2));
    }
    else{
        Coordinates c1(0,0);
        Coordinates c2(7,0);
        pieces.push_back(std::make_unique<Rook>(color, c1));
        pieces.push_back(std::make_unique<Rook>(color, c2));
    }

    //Reine
    if(!color){
        Coordinates c(3,7);
        pieces.push_back(std::make_unique<Queen>(color, c));
    }
    else{
        Coordinates c(3,0);
        pieces.push_back(std::make_unique<Queen>(color, c));
    }
    //Roi
    if(!color){
        Coordinates c(4,7);
        pieces.push_back(std::make_unique<King>(color, c));
    }
    else{
        Coordinates c(4,0);
        pieces.push_back(std::make_unique<King>(color, c));
    }
}

Piece* Player::getPiece(Coordinates c){
    if(!c.onBoard()) return nullptr;
    size_t  i = 0;
    while(i < pieces.size() && pieces[i].get()->getCoordinates()!=c){
        i++;
    }
    if(i < pieces.size()){
        return pieces[i].get();
    }
    return nullptr;
}

bool operator==(const Player &a,const Player &b)
{
    if(a.color!=b.color) return false;
    if(a.pieces.size()!=b.pieces.size()) return false;
    for(std::size_t i=0;i<a.pieces.size();i++)
    {
        bool found=false;
        std::size_t j=0;
        while(j<b.pieces.size())
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

bool Player::isPiece(Piece * p, size_t i)
{
    return p == pieces[i].get();
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

void Player::addPiece(std::unique_ptr<Piece> p)
{
    pieces.push_back(std::move(p));
}

void Player::removePiece(Coordinates c){
    size_t i=0;
    while(i<pieces.size() && pieces[i].get()->getCoordinates()!=c){
        i++;
    }
    if(i<pieces.size()) pieces.erase(pieces.begin()+i);
}

void Player::removePiece(size_t i){
    if(i < nbOfPieces()) pieces.erase(pieces.begin()+i);
}