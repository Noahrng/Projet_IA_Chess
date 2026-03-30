#ifndef ROOK_HPP
#define ROOK_HPP

#include "pieces.hpp"

class Rook : public Piece{
    private:
        static const Coordinates vect_move[];
        static const int vect_move_size;
    public:
        //Constructeurs/Destructeurs
        Rook(bool, Coordinates);
        
        PieceType getType() const override;
        const Coordinates* getVectMove() override;
        int getVectMoveSize() override;
        
        bool canMovePattern(const Coordinates) const override;
        bool canEatPattern(const Coordinates) const override;
};

#endif