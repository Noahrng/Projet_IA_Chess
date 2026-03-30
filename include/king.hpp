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
        bool canMovePattern(const Coordinates)const override;
        bool canEatPattern(const Coordinates)const override;
};

#endif