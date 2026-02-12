#include "../include/pieces.hpp"


Piece::Piece(bool col, Coordinates c) : color(col), coords(c){}

Coordinates Piece::getCoordinates()
{
    return this->coords;
}