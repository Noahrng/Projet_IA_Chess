#ifndef TOUR_HPP
#define TOUR_HPP

#include "pieces.hpp"

class Rook : public Piece{
    public:
        Rook(bool, Coordinates);
        bool canMove(Coordinates) override;
};

#endif