#include "../include/bishop.hpp"

Bishop::Bishop(bool col,Coordinates c): Piece(col,c,3,"♝"){}

bool Bishop::canMovePattern(Coordinates new_coords)
{
    if(!new_coords.onBoard()) return false;
    return coords.distX(new_coords) == coords.distY(new_coords) && coords != new_coords;
}

bool Bishop::canEatPattern(Coordinates new_coords)
{
    return canMovePattern(new_coords);
}

PieceType Bishop::getType() const
{
    return PieceType::Bishop;
}