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
        int getX() const;
        int getY() const;
        
        //Setters
        void setX(int);
        void setY(int);
        void setXY(int, int);

        //Comparaisons
        bool onBoard() const;
        bool lowerThanX(Coordinates) const;
        bool lowerThanY(Coordinates) const;
        bool greaterThanX(Coordinates) const;
        bool greaterThanY(Coordinates) const;

        //Distances Entre Coordonnées
        int distX(const Coordinates&) const;
        int distX(const int) const;
        int distY(const Coordinates&) const;
        int distY(const int) const;
};


#endif