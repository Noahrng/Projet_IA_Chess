#ifndef KING_HPP
#define KING_HPP

#include <pieces.hpp>

class King:public Piece{
    private:
        static std::vector<Coordinates> vect_move;
    public:
        //Constructeurs/Destructeurs
        King(bool,Coordinates);

        //Getters
        PieceType getType() const override;
        std::vector<Coordinates>& getVectMove() override;
        
        //Modèles de mouvement/capture
        bool canMovePattern(Coordinates) override;
        bool canEatPattern(Coordinates) override;
};

#endif