#ifndef BISHOP_HPP
#define BISHOP_HPP

#include "pieces.hpp"

class Bishop : public Piece{
    private:
        static std::vector<Coordinates> vect_move;
    public:
        Bishop(bool, Coordinates);
        
        //Getters
        PieceType getType() const override;
        std::vector<Coordinates>& getVectMove() override;
        
        //Modèles de mouvement/capture
        bool canMovePattern(const Coordinates) const override;
        bool canEatPattern(const Coordinates) const override;
};

#endif