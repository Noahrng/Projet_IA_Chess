#include "../include/queen.hpp"
#include "../include/bishop.hpp"
#include "../include/rook.hpp"

Queen::Queen(bool col,Coordinates c): Piece(col,c,9.0,"♛"){}

bool Queen::canMovePattern(Coordinates new_coords){
    if(!new_coords.onBoard()) return false;

    Bishop b(color, coords);
    Rook r(color, coords);

    return b.canMovePattern(new_coords) || r.canMovePattern(new_coords);
}

bool Queen::canEatPattern(Coordinates new_coords)
{
    return canMovePattern(new_coords);
}

PieceType Queen::getType() const
{
    return PieceType::Queen;
};