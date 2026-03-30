#ifndef KING_HPP
#define KING_HPP

#include <pieces.hpp>

class King:public Piece{
    private:
        static const Coordinates vect_move[];
        static const int vect_move_size;
    public:
        //Constructeurs/Destructeurs
        King(bool,Coordinates);

        //Getters
        PieceType getType() const override;
        const Coordinates* getVectMove() override;
        int getVectMoveSize() override;
        
        //Modèles de mouvement/capture
        bool canMovePattern(const Coordinates)const override;
        bool canEatPattern(const Coordinates)const override;
};

#endif