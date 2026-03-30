#include "../include/queen.hpp"
#include "../include/bishop.hpp"
#include "../include/rook.hpp"

/*----------------------Constructeurs / Destructeurs----------------------*/
Queen::Queen(bool col,Coordinates c): Piece(col,c,9.0,"♛")
{

}

/*-------------Vecteur Statique des Déplacements de la Reine--------------*/
std::vector<Coordinates> Queen::vect_move=
{
    Coordinates(0,1),Coordinates(0,2),Coordinates(0,3),Coordinates(0,4),Coordinates(0,5),Coordinates(0,6),Coordinates(0,7),
    Coordinates(0,-1),Coordinates(0,-2),Coordinates(0,-3),Coordinates(0,-4),Coordinates(0,-5),Coordinates(0,-6),Coordinates(0,-7),
    Coordinates(1,0),Coordinates(2,0),Coordinates(3,0),Coordinates(4,0),Coordinates(5,0),Coordinates(6,0),Coordinates(7,0),
    Coordinates(-1,0),Coordinates(-2,0),Coordinates(-3,0),Coordinates(-4,0),Coordinates(-5,0),Coordinates(-6,0),Coordinates(-7,0),
     Coordinates(1,1),Coordinates(2,2),Coordinates(3,3),Coordinates(4,4),Coordinates(5,5),Coordinates(6,6),Coordinates(7,7),
    Coordinates(-1,1),Coordinates(-2,2),Coordinates(-3,3),Coordinates(-4,4),Coordinates(-5,5),Coordinates(-6,6),Coordinates(-7,7),
    Coordinates(1,-1),Coordinates(2,-2),Coordinates(3,-3),Coordinates(4,-4),Coordinates(5,-5),Coordinates(6,-6),Coordinates(7,-7),
    Coordinates(-1,-1),Coordinates(-2,-2),Coordinates(-3,-3),Coordinates(-4,-4),Coordinates(-5,-5),Coordinates(-6,-6),Coordinates(-7,-7)
};

/*--------------------------------Getters---------------------------------*/
PieceType Queen::getType() const
{
    return PieceType::Queen;
};

std::vector<Coordinates>& Queen::getVectMove()
{
    return vect_move;
}

/*---------------------Modèles de mouvement/capture-----------------------*/
bool Queen::canMovePattern(const Coordinates new_coords) const
{
    if(!new_coords.onBoard()) return false;

    Bishop b(color, coords);
    Rook r(color, coords);

    return b.canMovePattern(new_coords) || r.canMovePattern(new_coords);
}

bool Queen::canEatPattern(const Coordinates new_coords) const
{
    return canMovePattern(new_coords);
}
