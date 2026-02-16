#ifndef BISHOP_HPP
#define BISHOP_HPP

#include "pieces.hpp"

class Bishop : public Piece{
    public:
        Bishop(bool, Coordinates);
        bool canMove(Coordinates) override;
        PieceType getType() const override;
};

#endif