#ifndef PIECES_HPP
#define PIECES_HPP

#include "coordinates.hpp"
#include <string>
#include <array>

typedef std::array<std::array<double,8>,8> Table8x8;

enum class PieceType
{
    Pawn=0,
    Rook,
    Knight,
    Bishop,
    Queen,
    King,
    Nothing
};

class Piece  {
    friend bool operator==(const Piece&,const Piece&);
    friend bool operator!=(const Piece&,const Piece&);
    protected:
        bool color; //0: blanc, 1: noir
        Coordinates coords;
        double value; //La valeur d'une pièce par rapport à une autre
        std::string terminal_sprite;
        Table8x8 position_table;
    public:
        Piece(bool, Coordinates, int, std::string);
        virtual ~Piece() = default;

        std::string getTerminalSprite();
        Coordinates getCoordinates();

        double getValue();

        virtual bool canMovePattern(Coordinates) = 0;
        virtual bool canEatPattern(Coordinates) = 0;
        virtual PieceType getType()const=0;
        double getPositionBonus();
        

        //virtual void onBeforeMove(Coordinates, Coordinates, Player*, Player*); Potentiellement utiles pour le futur
        //virtual void onAfterMove(Coordinates, Coordinates, Player*, Player*);


        void moveTo(int, int);
        void moveTo(Coordinates);
};


#endif