#include "../include/bishop.hpp"

/*----------------------Constructeurs / Destructeurs----------------------*/
Bishop::Bishop(bool col,Coordinates c): Piece(col,c,3.0,"♝")
{

}

/*----------------Tableau Statique des Déplacements du Fou----------------*/
const Coordinates Bishop::vect_move[]={
    Coordinates(1,1),Coordinates(2,2),Coordinates(3,3),Coordinates(4,4),Coordinates(5,5),Coordinates(6,6),Coordinates(7,7),
    Coordinates(-1,1),Coordinates(-2,2),Coordinates(-3,3),Coordinates(-4,4),Coordinates(-5,5),Coordinates(-6,6),Coordinates(-7,7),
    Coordinates(1,-1),Coordinates(2,-2),Coordinates(3,-3),Coordinates(4,-4),Coordinates(5,-5),Coordinates(6,-6),Coordinates(7,-7),
    Coordinates(-1,-1),Coordinates(-2,-2),Coordinates(-3,-3),Coordinates(-4,-4),Coordinates(-5,-5),Coordinates(-6,-6),Coordinates(-7,-7)
};

const int Bishop::vect_move_size = sizeof(vect_move) / sizeof(vect_move[0]);

/*--------------------------------Getters---------------------------------*/
PieceType Bishop::getType() const
{
    return PieceType::Bishop;
}

const Coordinates* Bishop::getVectMove()
{
    return vect_move;
}

int Bishop::getVectMoveSize()
{
    return vect_move_size;
}


/*---------------------Modèles de mouvement/capture-----------------------*/
bool Bishop::canMovePattern(const Coordinates new_coords) const
{
    if(!new_coords.onBoard()) return false;
    return coords.distX(new_coords) == coords.distY(new_coords) && coords != new_coords;
}

bool Bishop::canEatPattern(const Coordinates new_coords) const
{
    return canMovePattern(new_coords);
}
