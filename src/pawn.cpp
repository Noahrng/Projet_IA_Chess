#include "../include/pawn.hpp"

/*----------------------Constructeurs / Destructeurs----------------------*/
Pawn::Pawn(bool col,Coordinates c):Piece(col,c,1.0,"♟")
{
    
}

/*---------------Tableau Statique des Déplacements du Pion----------------*/
const Coordinates Pawn::vect_move[]={
    Coordinates(0,1),Coordinates(0,2),Coordinates(1,1),Coordinates(-1,1),
    Coordinates(0,-1),Coordinates(0,-2),Coordinates(1,-1),Coordinates(-1,-1),
};

const int Pawn::vect_move_size = sizeof(vect_move) / sizeof(vect_move[0]);

/*--------------------------------Getters---------------------------------*/
const Coordinates* Pawn::getVectMove()
{
    return vect_move;
}

int Pawn::getVectMoveSize()
{
    return vect_move_size;
}

PieceType Pawn::getType() const
{
    return PieceType::Pawn;
};

/*---------------------Modèles de mouvement/capture-----------------------*/
bool Pawn::canMovePattern(const Coordinates new_coords) const
{
    if(!new_coords.onBoard()) return false;

    int dist_x=this->coords.distX(new_coords);
    int dist_y=this->coords.distY(new_coords);


    if(dist_x==0)
    {
        if(color==false)
        {
            if(this->getCoordinates().getY() >= new_coords.getY()){
                if(dist_y>=1 && dist_y<=2 && this->coords.distY(6)==0)
                {
                    return true;
                }
                else if(dist_y == 1)
                {
                    return true;
                }
            }
        }
        else
        {
            if(this->getCoordinates().getY() <= new_coords.getY()){
                if(dist_y>=1 && dist_y<=2 && this->coords.distY(1)==0)
                {
                    return true;
                }
                else if(dist_y == 1)
                {
                    return true;
                }
            }
        }
    }
    return false;
    
}

bool Pawn::canEatPattern(const Coordinates new_coords) const
{
    if(!new_coords.onBoard()) return false;

    int dir = (color==1) ? 1 : -1;
    if(new_coords == Coordinates(coords.getX()-1,coords.getY()+dir) ||
        new_coords == Coordinates(coords.getX()+1, coords.getY()+dir))
    {
        return true;
    }

    return false;
}


