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
        Retourne le caractère correspondant a la pièce
*/
{
    return terminal_sprite;
}

Coordinates Piece::getCoordinates() const
/*
    Description:
        Retourne la coordonnée de la pièce
*/
{
    return this->coords;
}

double Piece::getValue() const
/*
    Description:
        Retourne la valeur de la pièce
*/
{
    return value;
}

/*--------------------------Nombre De Mouvements--------------------------*/
int Piece::howManyMoves() const
/*
    Description:
        Retourne le nombre de fois que la pièce a bougé
*/
{
    return nb_of_moves;
}

void Piece::incrementNbOfMoves()
/*
    Description:
        Incrèmente nb_of_moves
*/
{
    nb_of_moves++;
}

void Piece::decrementNbOfMoves()
/*
    Description:
        Décrèmente nb_of_moves
*/
{
    nb_of_moves--;
}

/*------------------------------Déplacement-------------------------------*/
void Piece::moveTo(int x, int y)
/*
    Description:
        Déplace la pièce avec deux entiers x,y
*/
{
    coords.setXY(x,y);
}

void Piece::moveTo(Coordinates c)
/*
    Description:
        Déplace la pièce avec une coordonnée c
*/
{
    coords = c;
}