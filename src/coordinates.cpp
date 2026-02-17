#include "../include/coordinates.hpp"

int abs(int n){
    if(n<0) return -n;
    return n;
}

Coordinates::Coordinates(){
    
}

Coordinates::Coordinates(int x,int y): x{x},y{y}
{

}

bool operator==(const Coordinates &a,const Coordinates &b)
{
    return a.x==b.x && a.y==b.y;
}

bool operator!=(const Coordinates &a,const Coordinates &b)
{
    return !(a==b);
}

int Coordinates::getX()
/*
    Arguments:
        void

    Description:
        retourne la valeur X courante

    Retour:
        int
*/
{
    return this->x;
}

int Coordinates::getY()
/*
    Arguments:
        void

    Description:
        retourne la valeur X courrante

    Retour:
        int
*/
{
    return this->y;
}

void Coordinates::setX(int new_x){
    x = new_x;
}

void Coordinates::setY(int new_y){
    y = new_y;
}

void Coordinates::setXY(int new_x,int new_y){
    x = new_x;
    y = new_y;
}

bool Coordinates::onBoard()
{
    if(x>=0 && x<8 && y>=0 && y<8) return true;
    return false;
}

//Equivalences
int Coordinates::lowerX(Coordinates c){
    if(c.x < x) return c.x;
    return x;
}
int Coordinates::lowerY(Coordinates c){
    if(c.y < y) return c.y;
    return y;
}
int Coordinates::greaterX(Coordinates c){
    if(c.x < x) return x;
    return c.x;
}
int Coordinates::greaterY(Coordinates c){
    if(c.y < y) return y;
    return c.y;
}

//Distances
int Coordinates::distX(const Coordinates &other)
{
    return abs(this->x-other.x);
}

int Coordinates::distY(const Coordinates &other)
{
    return abs(this->y-other.y);
}

int Coordinates::distX(const int X)
{
    return abs(this->x-X);
}
int Coordinates::distY(const int Y)
{
    return abs(this->y-Y);
}

//Affichage
void Coordinates::print(){
    std::cout<<"x="<<x<<" y="<<y<<"\n";
}