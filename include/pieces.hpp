#ifndef PIECES_HPP
#define PIECES_HPP

#include "coordinates.hpp"

class Piece{
    protected:
        bool color; //0: blanc, 1: noir
        Coordinates coords;
    public:
        Piece(bool, Coordinates);
        virtual ~Piece() = default;
        virtual bool canMove(Coordinates) = 0;
};

#endif