#ifndef COORDINATES_HPP
#define COORDINATES_HPP

#include <iostream>

class Coordinates{
    friend bool operator==(const Coordinates&,const Coordinates&);
    friend bool operator!=(const Coordinates&,const Coordinates&);
    friend bool operator<(const Coordinates&,const Coordinates&);

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

    friend Coordinates operator/(const Coordinates&,const int&);

    friend std::ostream& operator<<(std::ostream&, Coordinates&);
    private:
        int x;
        int y;
    public:
        //Constructeurs / Destructeurs
        Coordinates();
        Coordinates(int,int);
        ~Coordinates()=default;

        //Surcharge d'Opérateurs
        Coordinates& operator+=(const Coordinates&);
        Coordinates& operator+=(const int&);
        Coordinates& operator-=(const Coordinates&);
        Coordinates& operator-=(const int&);
        Coordinates& operator*=(const Coordinates&);
        Coordinates& operator*=(const int&);
        Coordinates& operator/=(const int&);

        //Getters
        int getX();
        int getY();
        
        //Setters
        void setX(int);
        void setY(int);
        void setXY(int, int);

        //Comparaisons
        bool onBoard();
        bool lowerThanX(Coordinates);
        bool lowerThanY(Coordinates);
        bool greaterThanX(Coordinates);
        bool greaterThanY(Coordinates);

        //Distances Entre Coordonnées
        int distX(const Coordinates&);
        int distX(const int);
        int distY(const Coordinates&);
        int distY(const int);

        //Affichage
        void print();
};


#endif