#ifndef PAWN_HPP
#define PAWN_HPP

#include "pieces.hpp"
#include "player.hpp"

class Pawn:public Piece{
    private:
        static std::vector<Coordinates> vect_move;
    public:
        Pawn(bool,Coordinates);
        
        //Getters
        PieceType getType() const override;
        std::vector<Coordinates>& getVectMove() override;
        
        //Modèles de mouvement/capture
        bool canMovePattern(Coordinates) override;
        bool canEatPattern(Coordinates) override;
};

#endif