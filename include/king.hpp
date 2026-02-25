#ifndef KING_HPP
#define KING_HPP

#include <pieces.hpp>

class King:public Piece{
    public:
        King(bool,Coordinates);
        bool canMovePattern(Coordinates) override;
        bool canEatPattern(Coordinates) override;
        PieceType getType() const override;
};

#endif