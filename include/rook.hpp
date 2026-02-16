#ifndef ROOK_HPP
#define ROOK_HPP

#include "pieces.hpp"

class Rook : public Piece{
    public:
        Rook(bool, Coordinates);
        bool canMove(Coordinates) override;
        PieceType getType() const override;
};

#endif