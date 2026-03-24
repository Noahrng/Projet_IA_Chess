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
std::string Piece::getTerminalSprite(){
    return terminal_sprite;
}

Coordinates Piece::getCoordinates()
{
    return this->coords;
}

double Piece::getValue()
{
    return value;
}

/*--------------------------Nombre De Mouvements--------------------------*/
int Piece::howManyMoves()
{
    return nb_of_moves;
}

void Piece::incrementNbOfMoves()
{
    nb_of_moves++;
}

void Piece::decrementNbOfMoves()
{
    nb_of_moves--;
}

/*------------------------------Déplacement-------------------------------*/
void Piece::moveTo(int x, int y){
    coords.setXY(x,y);
}

void Piece::moveTo(Coordinates c)
{
    coords = c;
}