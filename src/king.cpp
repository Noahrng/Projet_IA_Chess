#include "../include/king.hpp"

bool King::canMove(Coordinates coord)
{
    int distx=this->coords.distX(coord);
    int disty=this->coords.distY(coord);

    if((distx==1 || disty==1) && coords!=coord)
    {
        return true;
    }

    return false;
}

