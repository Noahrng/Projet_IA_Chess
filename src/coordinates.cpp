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

std::ostream& operator<<(std::ostream& os, Coordinates &a)
{
    os<<"x="<<a.getX()<<" y="<<a.getY()<< " ";
    return os;
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
bool Coordinates::lowerThanX(Coordinates c){
    if(c.x < x) return false;
    return true;
}
bool Coordinates::lowerThanY(Coordinates c){
    if(c.y < y) return false;
    return true;
}
bool Coordinates::greaterThanX(Coordinates c){
    if(c.x < x) return true;
    return false;
}
bool Coordinates::greaterThanY(Coordinates c){
    if(c.y < y) return true;
    return false;
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
    std::cout<< this;
}