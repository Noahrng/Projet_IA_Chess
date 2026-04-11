#include "../include/coordinates.hpp"

/*----------------------Constructeurs / Destructeurs----------------------*/
Coordinates::Coordinates(){
    
}

Coordinates::Coordinates(int x,int y): x{x},y{y}
{

}

/*------------------------Surcharge d'Opérateurs--------------------------*/
bool operator==(const Coordinates &a,const Coordinates &b)
{
    return a.x==b.x && a.y==b.y;
}

bool operator!=(const Coordinates &a,const Coordinates &b)
{
    return !(a==b);
}

bool operator<(const Coordinates &a,const Coordinates &b)
{
    if(a.x!=b.x) return a.x<b.x;
    return a.y<b.y;
}

Coordinates operator+(const Coordinates &a,const Coordinates &b)
{
    return Coordinates(a.x+b.x,a.y+b.y);
}

Coordinates operator+(const Coordinates &a,const int &lambda)
{
    return Coordinates(a.x+lambda,a.y+lambda);
}

Coordinates operator+(const int &lambda,const Coordinates &a)
{
    return Coordinates(a.x+lambda,a.y+lambda);
}

Coordinates operator-(const Coordinates &a,const Coordinates &b)
{
    return Coordinates(a.x-b.x,a.y-b.y);
}

Coordinates operator-(const Coordinates &a)
{
    return Coordinates(-a.x,-a.y);
}

Coordinates operator-(const Coordinates &a,const int &lambda)
{
    return Coordinates(a.x-lambda,a.y-lambda);
}

Coordinates operator-(const int &lambda,const Coordinates &a)
{
    return Coordinates(a.x-lambda,a.y-lambda);
}

Coordinates operator*(const Coordinates &a,const Coordinates &b)
{
    return Coordinates(a.x*b.x,a.y*b.y);
}

Coordinates operator*(const int &lambda,const Coordinates &a)
{
    return Coordinates(a.x*lambda,a.y*lambda);
}

Coordinates operator*(const Coordinates &a,const int &lambda)
{
    return Coordinates(a.x*lambda,a.y*lambda);
}

Coordinates operator/(const Coordinates &a,const int &lambda)
{
    return Coordinates(a.x/lambda,a.y/lambda);
}

Coordinates& Coordinates::operator+=(const Coordinates& other)
{
    x += other.x;
    y += other.y;
    return *this;
}

Coordinates& Coordinates::operator+=(const int &lambda)
{
    x += lambda;
    y += lambda;
    return *this;
}

Coordinates& Coordinates::operator-=(const Coordinates& other)
{
    x -= other.x;
    y -= other.y;
    return *this;
}

Coordinates& Coordinates::operator-=(const int &lambda)
{
    x -= lambda;
    y -= lambda;
    return *this;
}

Coordinates& Coordinates::operator*=(const Coordinates& other)
{
    x *= other.x;
    y *= other.y;
    return *this;
}

Coordinates& Coordinates::operator*=(const int &lambda)
{
    x *= lambda;
    y *= lambda;
    return *this;
}

Coordinates& Coordinates::operator/=(const int &lambda)
{
    x /= lambda;
    y /= lambda;
    return *this;
}


std::ostream& operator<<(std::ostream& os, Coordinates &a)
{
    os<<"x="<<a.getX()<<" y="<<a.getY()<< " ";
    return os;
}

/*--------------------------------Getters---------------------------------*/
int Coordinates::getX() const
/*
    Description:
        retourne la valeur X courante
*/
{
    return this->x;
}

int Coordinates::getY() const
/*
    Description:
        retourne la valeur Y courrante
*/
{
    return this->y;
}

/*--------------------------------Setters---------------------------------*/
void Coordinates::setX(int new_x)
/*
    Description:
        affecte une nouvelle valeur a X
*/
{
    x = new_x;
}

void Coordinates::setY(int new_y)
/*
    Description:
        affecte une nouvelle valeur a Y
*/
{
    y = new_y;
}

void Coordinates::setXY(int new_x,int new_y)
/*
    Description:
        affecte des nouvelles valeurs a X et Y
*/
{
    x = new_x;
    y = new_y;
}

/*------------------------------Comparaisons------------------------------*/
bool Coordinates::onBoard() const
/*
    Description:
        renvoie si la coordonnée courant est contenu dans un plateau d'echec 8x8
*/
{
    if(x>=0 && x<8 && y>=0 && y<8) return true;
    return false;
}

bool Coordinates::lowerThanX(Coordinates c) const
/*
    Description:
        Verifie sur l'abscisse de la coordonnée courant est inferieur ou égale a l'abscisse de c
*/
{
    if(c.x < x) return false;
    return true;
}

bool Coordinates::lowerThanY(Coordinates c) const
/*
    Description:
        Verifie sur l'ordonnée de la coordonnée courant est inferieur ou égale a l'ordonnée de c
*/
{
    if(c.y < y) return false;
    return true;
}

bool Coordinates::greaterThanX(Coordinates c) const 
/*
    Description:
        Verifie sur l'abscisse de la coordonnée courant est strictement supérieur a l'abscisse de c
*/
{
    if(c.x < x) return true;
    return false;
}

bool Coordinates::greaterThanY(Coordinates c) const 
/*
    Description:
        Verifie sur l'ordonnée de la coordonnée courant est strictement supérieur a l'ordonnée de c
*/
{
    if(c.y < y) return true;
    return false;
}

/*----------------------Distances Entre Coordonnées-----------------------*/
int Coordinates::distX(const Coordinates &other) const
/*
    Description:
        Calcule en renvoie la distance entre les deux abscisse
*/
{
    return std::abs(this->x-other.x);
}

int Coordinates::distX(const int X) const
/*
    Description:
        Calcule en renvoie la distance de l'abscisse courant et un autre entier X
*/
{
    return std::abs(this->x-X);
}

int Coordinates::distY(const Coordinates &other) const
/*
    Description:
        Calcule en renvoie la distance entre les deux ordonnées
*/
{
    return std::abs(this->y-other.y);
}

int Coordinates::distY(const int Y) const
/*
    Description:
        Calcule en renvoie la distance de l'ordonnée courant et un autre entier Y
*/
{
    return std::abs(this->y-Y);
}