#include "../include/pawn.hpp"

Pawn::Pawn(bool col,Coordinates c):Piece(col,c,1,"♟")
{
    
}

bool Pawn::canMovePattern(Coordinates new_coords)
{
    if(!new_coords.onBoard()) return false;

    int dist_x=this->coords.distX(new_coords);
    int dist_y=this->coords.distY(new_coords);


    if(dist_x==0)
    {
        if(color==false)
        {
            if(this->getCoordinates().getY() >= new_coords.getY()){
                if(dist_y>=1 && dist_y<=2 && this->coords.distY(6)==0)
                {
                    return true;
                }
                else if(dist_y == 1)
                {
                    return true;
                }
            }
        }
        else
        {
            if(this->getCoordinates().getY() <= new_coords.getY()){
                if(dist_y>=1 && dist_y<=2 && this->coords.distY(1)==0)
                {
                    return true;
                }
                else if(dist_y == 1)
                {
                    return true;
                }
            }
        }
    }
    return false;
    
}

bool Pawn::canEatPattern(Coordinates new_coords)
{
    if(!new_coords.onBoard()) return false;

    int dir = (color==1) ? 1 : -1;
    if(new_coords == Coordinates(coords.getX()-1,coords.getY()+dir) ||
        new_coords == Coordinates(coords.getX()+1, coords.getY()+dir))
    {
        return true;
    }

    return false;
}

PieceType Pawn::getType() const
{
    return PieceType::Pawn;
};


