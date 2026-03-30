#include "../include/king.hpp"

/*----------------------Constructeurs / Destructeurs----------------------*/
King::King(bool col,Coordinates c):Piece(col,c,1000.0,"♚")
{

}

/*----------------Tableau Statique des Déplacements du Roi----------------*/

const Coordinates King::vect_move[]=
{
    Coordinates(-1,-1),Coordinates(-1,0),Coordinates(-1,1),
    Coordinates(0,-1),Coordinates(0,1),
    Coordinates(1,-1),Coordinates(1,0),Coordinates(1,1),
    Coordinates(2,0),Coordinates(-2,0)
};

const int King::vect_move_size = sizeof(vect_move) / sizeof(vect_move[0]);

/*--------------------------------Getters---------------------------------*/
PieceType King::getType() const
{
    return PieceType::King;
};

const Coordinates* King::getVectMove()
{
    return vect_move;
}

int King::getVectMoveSize()
{
    return vect_move_size;
}

/*---------------------Modèles de mouvement/capture-----------------------*/
bool King::canMovePattern(const Coordinates new_coords) const
{
    if(!new_coords.onBoard()) return false;

    int distx=this->coords.distX(new_coords);
    int disty=this->coords.distY(new_coords);

    if((distx<=1 && disty<=1) && coords!=new_coords)
    {
        return true;
    }

    return false;
}

bool King::canEatPattern(const Coordinates new_coords) const
{
    return canMovePattern(new_coords);
}

