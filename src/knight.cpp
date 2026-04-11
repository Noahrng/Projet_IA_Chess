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
/*
    Description:
        Retourne le type de la pièce
*/
{
    return PieceType::Knight;
};

std::vector<Coordinates>& Knight::getVectMove()
/*
    Description:
        Retourne une reférence sur un vecteur de mouvement de base de la pièce
*/
{
    return vect_move;
}

/*---------------------Modèles de mouvement/capture-----------------------*/
bool Knight::canMovePattern(const Coordinates new_coords) const
/*
    Description:
        verifie si un mouvement peut être réaliser selon les règles déplacement de la pièce
*/
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
/*
    Description:
        verifie si un mouvement de capture peut être réaliser selon les règles déplacement de la pièce
*/
{
    return canMovePattern(new_coords);
}

