#include "../include/bishop.hpp"

/*----------------------Constructeurs / Destructeurs----------------------*/
Bishop::Bishop(bool col,Coordinates c): Piece(col,c,3.0,"♝")
{

}

/*----------------Vecteur Statique des Déplacements du Fou----------------*/
std::vector<Coordinates> Bishop::vect_move={
    Coordinates(1,1),Coordinates(2,2),Coordinates(3,3),Coordinates(4,4),Coordinates(5,5),Coordinates(6,6),Coordinates(7,7),
    Coordinates(-1,1),Coordinates(-2,2),Coordinates(-3,3),Coordinates(-4,4),Coordinates(-5,5),Coordinates(-6,6),Coordinates(-7,7),
    Coordinates(1,-1),Coordinates(2,-2),Coordinates(3,-3),Coordinates(4,-4),Coordinates(5,-5),Coordinates(6,-6),Coordinates(7,-7),
    Coordinates(-1,-1),Coordinates(-2,-2),Coordinates(-3,-3),Coordinates(-4,-4),Coordinates(-5,-5),Coordinates(-6,-6),Coordinates(-7,-7)
};

/*--------------------------------Getters---------------------------------*/
PieceType Bishop::getType() const
{
    return PieceType::Bishop;
}

std::vector<Coordinates>& Bishop::getVectMove()
{
    return vect_move;
}

/*---------------------Modèles de mouvement/capture-----------------------*/
bool Bishop::canMovePattern(Coordinates new_coords)
{
    if(!new_coords.onBoard()) return false;
    return coords.distX(new_coords) == coords.distY(new_coords) && coords != new_coords;
}

bool Bishop::canEatPattern(Coordinates new_coords)
{
    return canMovePattern(new_coords);
}
