#ifndef KING_HPP
#define KING_HPP

#include <pieces.hpp>

class King:public Piece{
    private:
        static std::vector<Coordinates> vect_move;
    public:
        King(bool,Coordinates);
        bool canMovePattern(Coordinates) override;
        bool canEatPattern(Coordinates) override;
        PieceType getType() const override;
        std::vector<Coordinates>& getVectMove() override;
};

#endif