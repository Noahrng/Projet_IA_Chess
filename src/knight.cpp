#include <knight.hpp>

bool Knight::canMove(Coordinates coord)
{
    int distx=this->coords.distX(coord);
    int disty=this->coords.distY(coord);

    if((distx==1 && disty ==2) ||(distx==2 && disty==1))
    {
        return true;
    }
    return false;
}

