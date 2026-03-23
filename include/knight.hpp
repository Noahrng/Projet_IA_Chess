#ifndef KNIGHT_HPP
#define KNIGHT_HPP

#include <pieces.hpp>

class Knight:public Piece{
    private:
        static std::vector<Coordinates> vect_move;
    public:
        Knight(bool,Coordinates);
        bool canMovePattern(Coordinates) override;
        bool canEatPattern(Coordinates) override;
        PieceType getType() const override;
        std::vector<Coordinates>& getVectMove() override;
};

#endif