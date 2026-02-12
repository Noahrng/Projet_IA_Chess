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
        Coordinates c1(7,1);
        Coordinates c2(7,6);
        pieces.push_back(std::make_unique<Knight>(color, c1));
        pieces.push_back(std::make_unique<Knight>(color, c2));
    }
    else{
        Coordinates c1(0,1);
        Coordinates c2(0,6);
        pieces.push_back(std::make_unique<Knight>(color, c1));
        pieces.push_back(std::make_unique<Knight>(color, c2));
    }

    //Fous
    if(!color){
        Coordinates c1(7,2);
        Coordinates c2(7,5);
        pieces.push_back(std::make_unique<Bishop>(color, c1));
        pieces.push_back(std::make_unique<Bishop>(color, c2));
    }
    else{
        Coordinates c1(0,2);
        Coordinates c2(0,5);
        pieces.push_back(std::make_unique<Bishop>(color, c1));
        pieces.push_back(std::make_unique<Bishop>(color, c2));
    }
    //Tours
    if(!color){
        Coordinates c1(7,0);
        Coordinates c2(7,7);
        pieces.push_back(std::make_unique<Rook>(color, c1));
        pieces.push_back(std::make_unique<Rook>(color, c2));
    }
    else{
        Coordinates c1(0,0);
        Coordinates c2(0,7);
        pieces.push_back(std::make_unique<Rook>(color, c1));
        pieces.push_back(std::make_unique<Rook>(color, c2));
    }

    //Reine
    if(!color){
        Coordinates c(7,3);
        pieces.push_back(std::make_unique<Queen>(color, c));
    }
    else{
        Coordinates c(0,3);
        pieces.push_back(std::make_unique<Queen>(color, c));
    }
    //Roi
    if(!color){
        Coordinates c(7,4);
        pieces.push_back(std::make_unique<King>(color, c));
    }
    else{
        Coordinates c(0,4);
        pieces.push_back(std::make_unique<King>(color, c));
    }
}

Piece* Player::getPiece(Coordinates c){
    size_t i = 0;
    while(i < pieces.size() && pieces[i].get()->getCoordinates()!=c){
        i++;
    }
    if(i < pieces.size()){
        return pieces[i].get();
    }
    return nullptr;
}

void Player::addPiece(std::unique_ptr<Piece> p){
    pieces.push_back(std::move(p));
}

void Player::removePiece(Coordinates c){
    size_t i=0;
    while(i<pieces.size() && pieces[i].get()->getCoordinates()!=c){
        i++;
    }
    if(i<pieces.size()) pieces.erase(pieces.begin()+i);
}

Piece* Player::getPiece(Coordinates c){
    size_t i=0;
    while(i<pieces.size() && pieces[i].get()->getCoordinates()!=c){
        i++;
    }
    if(i<pieces.size()) return pieces[i].get();
    return nullptr;
}
    