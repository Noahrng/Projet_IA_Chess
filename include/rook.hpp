#ifndef ROOK_HPP
#define ROOK_HPP

#include "pieces.hpp"

class Rook : public Piece{
    private:
        static std::vector<Coordinates> vect_move;
    public:
        //Constructeurs/Destructeurs
        Rook(bool, Coordinates);
        
        PieceType getType() const override;
        std::vector<Coordinates>& getVectMove() override;
        
        bool canMovePattern(Coordinates) override;
        bool canEatPattern(Coordinates) override;
};

#endif