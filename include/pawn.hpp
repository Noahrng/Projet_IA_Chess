#ifndef PAWN_HPP
#define PAWN_HPP

#include <pieces.hpp>

class Pawn:public Piece{
    public:
        bool canMove(Coordinates) override;
};

#endif