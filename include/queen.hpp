#ifndef QUEEN_HPP
#define QUEEN_HPP

#include "pieces.hpp"

class Queen : public Piece{
    private:
        static std::vector<Coordinates> vect_move;
    public:
        Queen(bool, Coordinates);
        bool canMovePattern(Coordinates) override;
        bool canEatPattern(Coordinates) override;
        PieceType getType() const override;
        std::vector<Coordinates>& getVectMove() override;
};

#endif