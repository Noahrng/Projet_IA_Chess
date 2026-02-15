#ifndef PIECES_HPP
#define PIECES_HPP

#include "coordinates.hpp"
#include <string>

enum class PieceType
{
    Pawn=0,
    Rook,
    Knight,
    Bishop,
    Queen,
    King
};

class Piece  {
    friend bool operator==(const Piece&,const Piece&);
    friend bool operator!=(const Piece&,const Piece&);
    protected:
        bool color; //0: blanc, 1: noir
        Coordinates coords;
        int value; //La valeur d'une pièce par rapport à une autre
        std::string terminal_sprite;
    public:
        Piece(bool, Coordinates, int, std::string);

        std::string getTerminalSprite();
        Coordinates getCoordinates();
        virtual ~Piece() = default;

        virtual bool canMove(Coordinates) = 0;
        virtual PieceType getType()const=0;
};


#endif