#ifndef BISHOP_HPP
#define BISHOP_HPP

#include "pieces.hpp"

class Bishop : public Piece{
    private:
        static std::vector<Coordinates> vect_move;
    public:
        Bishop(bool, Coordinates);
        bool canMovePattern(Coordinates) override;
        bool canEatPattern(Coordinates) override;
        PieceType getType() const override;
        std::vector<Coordinates>& getVectMove() override;
};

#endif