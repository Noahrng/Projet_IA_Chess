#ifndef PIECES_HPP
#define PIECES_HPP

#include "coordinates.hpp"

class Piece  {
    protected:
        bool color; //0: blanc, 1: noir
        Coordinates coords;
        int value; //La valeur d'une pièce par rapport à une autre
    public:
        Piece(bool, Coordinates, int);
        Coordinates getCoordinates();
        virtual ~Piece() = default;
        virtual bool canMove(Coordinates) = 0;
};

#endif