#include "../include/pieces.hpp"

#include <iostream>
Piece::Piece(bool col, Coordinates c,int v, std::string ts) : color(col), coords(c), value(v), terminal_sprite(ts){}

bool operator==(const Piece &a,const Piece &b)
{
    return a.color==b.color && a.coords==b.coords;
}
bool operator!=(const Piece &a,const Piece &b)
{
    return !(a==b);
}

std::string Piece::getTerminalSprite(){
    return terminal_sprite;
}

Coordinates Piece::getCoordinates()
{
    return this->coords;
}

void Piece::moveTo(int x, int y){
    coords.setXY(x,y);
}