#ifndef PAWN_HPP
#define PAWN_HPP

#include <pieces.hpp>

class Pawn:public Piece{
    public:
        Pawn(bool,Coordinates);
        bool canMove(Coordinates) override;
};

#endif