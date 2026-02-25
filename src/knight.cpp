#include "../include/knight.hpp"

Knight::Knight(bool col,Coordinates c):Piece(col,c,3,"♞")
{

}

bool Knight::canMovePattern(Coordinates new_coords)
{
    if(!new_coords.onBoard()) return false;

    int distx=this->coords.distX(new_coords);
    int disty=this->coords.distY(new_coords);

    if((distx==1 && disty ==2) ||(distx==2 && disty==1))
    {
        return true;
    }
    return false;
}

bool Knight::canEatPattern(Coordinates new_coords)
{
    return canMovePattern(new_coords);
}

PieceType Knight::getType() const
{
    return PieceType::Knight;
};

