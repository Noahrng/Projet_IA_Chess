#include "../include/knight.hpp"

/*----------------------Constructeurs / Destructeurs----------------------*/
Knight::Knight(bool col,Coordinates c):Piece(col,c,3.0,"♞")
{

}

/*-------------Vecteur Statique des Déplacements du Cavalier--------------*/
std::vector<Coordinates> Knight::vect_move={
    Coordinates(1,2),Coordinates(1,-2),Coordinates(-1,2),Coordinates(-1,-2),
    Coordinates(2,1),Coordinates(2,-1),Coordinates(-2,1),Coordinates(-2,-1)
};

/*--------------------------------Getters---------------------------------*/
PieceType Knight::getType() const
{
    return PieceType::Knight;
};

std::vector<Coordinates>& Knight::getVectMove()
{
    return vect_move;
}

/*---------------------Modèles de mouvement/capture-----------------------*/
bool Knight::canMovePattern(Coordinates new_coords)
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

bool Knight::canEatPattern(Coordinates new_coords)
{
    return canMovePattern(new_coords);
}

