#include "../include/rook.hpp"

Rook::Rook(bool col,Coordinates c): Piece(col,c,5,"♜"){}

bool Rook::canMovePattern(Coordinates new_coords)
{
    if(!new_coords.onBoard()) return false;
    return (coords.distX(new_coords) == 0) != (coords.distY(new_coords) == 0);
}

bool Rook::canEatPattern(Coordinates new_coords)
{
    return canMovePattern(new_coords);
}

PieceType Rook::getType() const
{
    return PieceType::Rook;
};