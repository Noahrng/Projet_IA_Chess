#ifndef KNIGHT_HPP
#define KNIGHT_HPP

#include <pieces.hpp>

class Knight:public Piece{
    private:
        static std::vector<Coordinates> vect_move;
    public:
        //Constructeurs/Destructeurs
        Knight(bool,Coordinates);

        //Getters
        PieceType getType() const override;
        std::vector<Coordinates>& getVectMove() override;
        
        //Modèles de mouvement/capture
        bool canMovePattern(const Coordinates)const override;
        bool canEatPattern(const Coordinates)const override;
};

#endif