#ifndef COORDINATES_HPP
#define COORDINATES_HPP

class Coordinates{
    private:
        int x;
        int y;
    public:
        Coordinates(int,int);
        ~Coordinates();
        int getX();
        int getY();
};


#endif