#include "../include/bishop.hpp"

Bishop::Bishop(bool col,Coordinates c): Piece(col,c,3,"♝"){}

bool Bishop::canMove(Coordinates new_coords)
{
    return coords.distX(new_coords) == coords.distY(new_coords) && coords != new_coords;
}

PieceType Bishop::getType() const
{
    return PieceType::Bishop;
}