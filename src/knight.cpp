#include "../include/knight.hpp"

/*----------------------Constructeurs / Destructeurs----------------------*/
Knight::Knight(bool col,Coordinates c):Piece(col,c,3.0,"♞")
{

}

/*-------------Tableau Statique des Déplacements du Cavalier--------------*/
const Coordinates Knight::vect_move[]={
    Coordinates(1,2),Coordinates(1,-2),Coordinates(-1,2),Coordinates(-1,-2),
    Coordinates(2,1),Coordinates(2,-1),Coordinates(-2,1),Coordinates(-2,-1)
};

const int Knight::vect_move_size = sizeof(vect_move) / sizeof(vect_move[0]);

/*--------------------------------Getters---------------------------------*/
PieceType Knight::getType() const
{
    return PieceType::Knight;
};

const Coordinates* Knight::getVectMove()
{
    return vect_move;
}

int Knight::getVectMoveSize()
{
    return vect_move_size;
}

/*---------------------Modèles de mouvement/capture-----------------------*/
bool Knight::canMovePattern(const Coordinates new_coords) const
{
    if(!new_coords.onBoard()) return false;

    int distx=this->coords.distX(new_coords);
    int disty=this->coords.distY(new_coords);

    if((distx==1 && disty ==2) ||(distx==2 && disty==1))
    {
        return true;
    }
    return false;
}

bool Knight::canEatPattern(const Coordinates new_coords) const
{
    return canMovePattern(new_coords);
}

