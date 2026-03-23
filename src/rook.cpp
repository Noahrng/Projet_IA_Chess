#include "../include/rook.hpp"

Rook::Rook(bool col,Coordinates c): Piece(col,c,5.0,"♜"){}

std::vector<Coordinates> Rook::vect_move={
    Coordinates(0,1),Coordinates(0,2),Coordinates(0,3),Coordinates(0,4),Coordinates(0,5),Coordinates(0,6),Coordinates(0,7),
    Coordinates(0,-1),Coordinates(0,-2),Coordinates(0,-3),Coordinates(0,-4),Coordinates(0,-5),Coordinates(0,-6),Coordinates(0,-7),
    Coordinates(1,0),Coordinates(2,0),Coordinates(3,0),Coordinates(4,0),Coordinates(5,0),Coordinates(6,0),Coordinates(7,0),
    Coordinates(-1,0),Coordinates(-2,0),Coordinates(-3,0),Coordinates(-4,0),Coordinates(-5,0),Coordinates(-6,0),Coordinates(-7,0)
};

std::vector<Coordinates>& Rook::getVectMove()
{
    return vect_move;
}

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