#ifndef ROOK_HPP
#define ROOK_HPP

#include "pieces.hpp"

class Rook : public Piece{
    private:
        static std::vector<Coordinates> vect_move;
    public:
        Rook(bool, Coordinates);
        bool canMovePattern(Coordinates) override;
        bool canEatPattern(Coordinates) override;
        PieceType getType() const override;
        std::vector<Coordinates>& getVectMove() override;
};

#endif