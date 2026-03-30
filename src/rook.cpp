#include "../include/rook.hpp"

/*----------------------Constructeurs / Destructeurs----------------------*/
Rook::Rook(bool col,Coordinates c): Piece(col,c,5.0,"♜")
{

}

/*--------------Tableau Statique des Déplacements de la Tour--------------*/
const Coordinates Rook::vect_move[]={
    Coordinates(0,1),Coordinates(0,2),Coordinates(0,3),Coordinates(0,4),Coordinates(0,5),Coordinates(0,6),Coordinates(0,7),
    Coordinates(0,-1),Coordinates(0,-2),Coordinates(0,-3),Coordinates(0,-4),Coordinates(0,-5),Coordinates(0,-6),Coordinates(0,-7),
    Coordinates(1,0),Coordinates(2,0),Coordinates(3,0),Coordinates(4,0),Coordinates(5,0),Coordinates(6,0),Coordinates(7,0),
    Coordinates(-1,0),Coordinates(-2,0),Coordinates(-3,0),Coordinates(-4,0),Coordinates(-5,0),Coordinates(-6,0),Coordinates(-7,0)
};

const int Rook::vect_move_size = sizeof(vect_move) / sizeof(vect_move[0]);

/*--------------------------------Getters---------------------------------*/
PieceType Rook::getType() const
{
    return PieceType::Rook;
};

const Coordinates* Rook::getVectMove()
{
    return vect_move;
}

int Rook::getVectMoveSize()
{
    return vect_move_size;
}

/*---------------------Modèles de mouvement/capture-----------------------*/
bool Rook::canMovePattern(const Coordinates new_coords) const
{
    if(!new_coords.onBoard()) return false;
    return (coords.distX(new_coords) == 0) != (coords.distY(new_coords) == 0);
}

bool Rook::canEatPattern(const Coordinates new_coords) const
{
    return canMovePattern(new_coords);
}
