#include "../include/rook.hpp"

/*----------------------Constructeurs / Destructeurs----------------------*/
Rook::Rook(bool col,Coordinates c): Piece(col,c,5.0,"♜")
{

}

/*--------------Vecteur Statique des Déplacements de la Tour--------------*/
std::vector<Coordinates> Rook::vect_move={
    Coordinates(0,1),Coordinates(0,2),Coordinates(0,3),Coordinates(0,4),Coordinates(0,5),Coordinates(0,6),Coordinates(0,7),
    Coordinates(0,-1),Coordinates(0,-2),Coordinates(0,-3),Coordinates(0,-4),Coordinates(0,-5),Coordinates(0,-6),Coordinates(0,-7),
    Coordinates(1,0),Coordinates(2,0),Coordinates(3,0),Coordinates(4,0),Coordinates(5,0),Coordinates(6,0),Coordinates(7,0),
    Coordinates(-1,0),Coordinates(-2,0),Coordinates(-3,0),Coordinates(-4,0),Coordinates(-5,0),Coordinates(-6,0),Coordinates(-7,0)
};

/*--------------------------------Getters---------------------------------*/
PieceType Rook::getType() const
/*
    Description:
        Retourne le type de la pièce
*/
{
    return PieceType::Rook;
};

std::vector<Coordinates>& Rook::getVectMove()
/*
    Description:
        Retourne une reférence sur un vecteur de mouvement de base de la pièce
*/
{
    return vect_move;
}

/*---------------------Modèles de mouvement/capture-----------------------*/
bool Rook::canMovePattern(const Coordinates new_coords) const
/*
    Description:
        verifie si un mouvement peut être réaliser selon les règles déplacement de la pièce
*/
{
    if(!new_coords.onBoard()) return false;
    return (coords.distX(new_coords) == 0) != (coords.distY(new_coords) == 0);
}

bool Rook::canEatPattern(const Coordinates new_coords) const
/*
    Description:
        verifie si un mouvement de capture peut être réaliser selon les règles déplacement de la pièce
*/
{
    return canMovePattern(new_coords);
}
