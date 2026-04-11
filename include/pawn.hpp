#ifndef PAWN_HPP
#define PAWN_HPP

#include "pieces.hpp"
#include "player.hpp"

class Pawn:public Piece{
    private:
        static std::vector<Coordinates> vect_move;
    public:
        //Constructeurs/Destructeurs
        Pawn(bool,Coordinates);

        //Getters
        PieceType getType() const override;
        std::vector<Coordinates>& getVectMove() override;
        
        //Modèles de mouvement/capture
        bool canMovePattern(const Coordinates) const override;
        bool canEatPattern(const Coordinates) const override;
};

#endif