#include "../include/pieces.hpp"


Piece::Piece(bool col, Coordinates c,int v) : color(col), coords(c), value(v){}

Coordinates Piece::getCoordinates()
{
    return this->coords;
}