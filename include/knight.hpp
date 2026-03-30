#ifndef KNIGHT_HPP
#define KNIGHT_HPP

#include <pieces.hpp>

class Knight:public Piece{
    private:
        static const Coordinates vect_move[];
        static const int vect_move_size;
    public:
        //Constructeurs/Destructeurs
        Knight(bool,Coordinates);

        //Getters
        PieceType getType() const override;
        const Coordinates* getVectMove() override;
        int getVectMoveSize() override;
        
        //Modèles de mouvement/capture
        bool canMovePattern(const Coordinates)const override;
        bool canEatPattern(const Coordinates)const override;
};

#endif