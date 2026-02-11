#ifndef COORDINATES_HPP
#define COORDINATES_HPP

//int abs(int);

class Coordinates{
    friend bool operator==(const Coordinates&,const Coordinates&);
    friend bool operator!=(const Coordinates&,const Coordinates&);
    private:
        int x;
        int y;
    public:
        Coordinates(int,int);
        ~Coordinates()=default;
        int distX(const Coordinates&);
        int distY(const Coordinates&);
        int distX(const int);
        int distY(const int);
        int getX();
        int getY();
};


#endif