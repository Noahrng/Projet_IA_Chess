#include "../include/pieces.hpp"

#include <iostream>
Piece::Piece(bool col, Coordinates c,int v, std::string ts) : color(col), coords(c), value(v), terminal_sprite(ts){}

bool operator==(const Piece &a,const Piece &b)
{
    std::cout<<"test\n";
    std::cout<<a.terminal_sprite << "[]"<<b.terminal_sprite<<"\n";
    return a.color==b.color && a.coords==b.coords;
}
bool operator!=(const Piece &a,const Piece &b)
{
    std::cout<<"test\n";
    std::cout<<a.terminal_sprite << "[]"<<b.terminal_sprite<<"\n";
    return a.color!=b.color || a.coords!=b.coords;
}

std::string Piece::getTerminalSprite(){
    return terminal_sprite;
}

Coordinates Piece::getCoordinates()
{
    return this->coords;
}