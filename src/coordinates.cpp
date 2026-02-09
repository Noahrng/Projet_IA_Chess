#include "coordinates.hpp"

Coordinates::Coordinates(int x,int y): x{x},y{y} {

}

int Coordinates::getX(){
    return this->x;
}

int Coordinates::getY(){
    return this->y;
}

