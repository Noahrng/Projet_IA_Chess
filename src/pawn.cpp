#include "../include/pawn.hpp"

Pawn::Pawn(bool col,Coordinates c):Piece(col,c,1)
{

}

bool Pawn::canMove(Coordinates coord)
{
    int dist=this->coords.distY(coord);
    if(color==false)
    {
        if(dist>=1 && dist<=2 && this->coords.distY(7)==0)
        {
            return true;
        }
        else if(dist == 1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        if(dist>=1 && dist<=2 && this->coords.distY(1)==0)
        {
            return true;
        }
        else if(dist == 1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

