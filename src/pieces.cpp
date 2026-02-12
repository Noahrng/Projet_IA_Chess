#include "../include/pieces.hpp"


Piece::Piece(bool col, Coordinates c,int v, std::string ts) : color(col), coords(c), value(v), terminal_sprite(ts){}

std::string Piece::getTerminalSprite(){
    return terminal_sprite;
}

Coordinates Piece::getCoordinates()
{
    return this->coords;
}