#ifndef KING_HPP
#define KING_HPP

#include <pieces.hpp>

class King:public Piece{
    public:
        King(bool,Coordinates);
        bool canMove(Coordinates) override;
        PieceType getType() const override;
};

#endif