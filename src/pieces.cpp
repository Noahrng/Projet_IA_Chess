#include "../include/pieces.hpp"
#include <iostream>

/*----------------------Constructeurs / Destructeurs----------------------*/
Piece::Piece(bool col, Coordinates c,int v, std::string ts) : 
    color(col), nb_of_moves(0), coords(c), value(v), terminal_sprite(ts)
{

}

Piece::Piece(bool col, int nb, Coordinates c, int v, std::string ts): 
    color(col), nb_of_moves(nb), coords(c), value(v), terminal_sprite(ts)
{

}

/*------------------------Surcharge d'Opérateurs--------------------------*/
bool operator==(const Piece &a,const Piece &b)
{
    return a.color==b.color && a.coords==b.coords;
}
bool operator!=(const Piece &a,const Piece &b)
{
    return !(a==b);
}

bool operator<(const Piece &a,const Piece &b)
{
    return a.coords<b.coords;
}

/*--------------------------------Getters---------------------------------*/
std::string Piece::getTerminalSprite() const
/*
    Description:
        retourne le caractère correspondant a la pièce
*/
{
    return terminal_sprite;
}

Coordinates Piece::getCoordinates() const
/*
    Description:
        retourne la coordonnée de la pièce
*/
{
    return this->coords;
}

double Piece::getValue() const
/*
    Description:
        retourne la valeur de la pièce
*/
{
    return value;
}

/*--------------------------Nombre De Mouvements--------------------------*/
int Piece::howManyMoves() const
/*
    Description:
        retourne le nombre de fois que la pièce a bouger
*/
{
    return nb_of_moves;
}

void Piece::incrementNbOfMoves()
/*
    Description:
        incremente le nb_of_moves
*/
{
    nb_of_moves++;
}

void Piece::decrementNbOfMoves()
/*
    Description:
        decremente le nb_of_moves
*/
{
    nb_of_moves--;
}

/*------------------------------Déplacement-------------------------------*/
void Piece::moveTo(int x, int y)
/*
    Description:
        déplace la pièce avec deux entier x,y
*/
{
    coords.setXY(x,y);
}

void Piece::moveTo(Coordinates c)
/*
    Description:
        déplace la pièce avec une coordonnée c
*/
{
    coords = c;
}