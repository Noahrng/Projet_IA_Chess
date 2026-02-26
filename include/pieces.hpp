#ifndef PIECES_HPP
#define PIECES_HPP

#include "coordinates.hpp"
#include <string>
#include "piece_type.hpp"

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
        virtual ~Piece() = default;

        std::string getTerminalSprite();
        Coordinates getCoordinates();

        virtual bool canMovePattern(Coordinates) = 0;
        virtual bool canEatPattern(Coordinates) = 0;
        virtual PieceType getType()const=0;

        //virtual void onBeforeMove(Coordinates, Coordinates, Player*, Player*); Potentiellement utiles pour le futur
        //virtual void onAfterMove(Coordinates, Coordinates, Player*, Player*);


        void moveTo(int, int);
        void moveTo(Coordinates);
};


#endif