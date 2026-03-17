#include "../include/king.hpp"

King::King(bool col,Coordinates c):Piece(col,c,1000.0,"♚")
{

}

std::vector<Coordinates> King::vect_move={
    Coordinates(-1,-1),Coordinates(-1,0),Coordinates(-1,1),
    Coordinates(0,-1),Coordinates(0,1),
    Coordinates(1,-1),Coordinates(1,0),Coordinates(1,1)
};

std::vector<Coordinates>& King::getVectMove()
{
    return vect_move;
}

bool King::canMovePattern(Coordinates new_coords)
{
    if(!new_coords.onBoard()) return false;

    int distx=this->coords.distX(new_coords);
    int disty=this->coords.distY(new_coords);

    if((distx<=1 && disty<=1) && coords!=new_coords)
    {
        return true;
    }

    return false;
}

bool King::canEatPattern(Coordinates new_coords)
{
    return canMovePattern(new_coords);
}

PieceType King::getType() const
{
    return PieceType::King;
};
