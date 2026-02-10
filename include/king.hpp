#ifndef KING_HPP
#define KING_HPP

#include <pieces.hpp>

class King:public Piece{
    public:
        bool canMove(Coordinates) override;
};

#endif