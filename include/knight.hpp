#ifndef KNIGHT_HPP
#define KNIGHT_HPP

#include <pieces.hpp>

class Knight:public Piece{
    public:
        Knight(bool,Coordinates);
        bool canMove(Coordinates) override;
};

#endif