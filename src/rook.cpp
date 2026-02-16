#include "../include/rook.hpp"

Rook::Rook(bool col,Coordinates c): Piece(col,c,5,"♜"){}

bool Rook::canMove(Coordinates new_coords)
{
    return (coords.distX(new_coords) == 0) != (coords.distY(new_coords) == 0);
}

PieceType Rook::getType() const
{
    return PieceType::Rook;
};