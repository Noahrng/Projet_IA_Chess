#ifndef COORDINATES_HPP
#define COORDINATES_HPP

#include <iostream>

class Coordinates{
    friend bool operator==(const Coordinates&,const Coordinates&);
    friend bool operator!=(const Coordinates&,const Coordinates&);

    friend Coordinates operator+(const Coordinates&,const Coordinates&);
    friend Coordinates operator+(const Coordinates&,const int&);
    friend Coordinates operator+(const int&,const Coordinates&);

    friend Coordinates operator-(const Coordinates&,const Coordinates&);
    friend Coordinates operator-(const Coordinates&);
    friend Coordinates operator-(const Coordinates&,const int&);
    friend Coordinates operator-(const int&,const Coordinates&);

    friend Coordinates operator*(const Coordinates&,const Coordinates&);
    friend Coordinates operator*(const int&,const Coordinates&);
    friend Coordinates operator*(const Coordinates&,const int&);

    friend std::ostream& operator<<(std::ostream&, Coordinates&);
    private:
        int x;
        int y;
    public:
        Coordinates();
        Coordinates(int,int);
        ~Coordinates()=default;

        //operator
        Coordinates& operator+=(const Coordinates&);
        Coordinates& operator+=(const int&);
        Coordinates& operator-=(const Coordinates&);
        Coordinates& operator-=(const int&);
        Coordinates& operator*=(const Coordinates&);
        Coordinates& operator*=(const int&);

        //Getters
        int getX();
        int getY();
        
        //Setters
        void setX(int);
        void setY(int);
        void setXY(int, int);

        //
        bool onBoard();

        //Equivalences
        bool lowerThanX(Coordinates);
        bool lowerThanY(Coordinates);
        bool greaterThanX(Coordinates);
        bool greaterThanY(Coordinates);

        //Distances entre coordonnées
        int distX(const Coordinates&);
        int distY(const Coordinates&);
        int distX(const int);
        int distY(const int);

        //Affichage
        void print();
};


#endif