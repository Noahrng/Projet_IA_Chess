#ifndef QUEEN_HPP
#define QUEEN_HPP

#include "pieces.hpp"

class Queen : public Piece{
    public:
        Queen(bool, Coordinates);
        bool canMove(Coordinates) override;
        PieceType getType() const override;
};

#endif