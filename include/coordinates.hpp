#ifndef COORDINATES_HPP
#define COORDINATES_HPP

#include <iostream>

class Coordinates{
    friend bool operator==(const Coordinates&,const Coordinates&);
    friend bool operator!=(const Coordinates&,const Coordinates&);
    private:
        int x;
        int y;
    public:
        Coordinates();
        Coordinates(int,int);
        ~Coordinates()=default;
        int distX(const Coordinates&);
        int distY(const Coordinates&);
        int distX(const int);
        int distY(const int);
        int getX();
        int getY();
        void setX(int);
        void setY(int);
        void setXY(int, int);
        void print();
};


#endif