#ifndef PIECES_HPP
#define PIECES_HPP

#include "coordinates.hpp"
#include <string>
#include "piece_type.hpp"
#include <vector>
#include <memory>

class Piece  {
    friend bool operator==(const Piece&,const Piece&);
    friend bool operator!=(const Piece&,const Piece&);
    friend bool operator<(const Piece&,const Piece&);
    
    protected:
        bool color; //0: blanc, 1: noir
        int nb_of_moves; //Nombre de mouvements de la pièce
        Coordinates coords;
        double value; //La valeur d'une pièce par rapport à une autre
        std::string terminal_sprite;
    public:
        //Constructeurs/Destructeurs
        Piece(bool, Coordinates, int, std::string);
        Piece(bool, int, Coordinates, int, std::string);
        virtual ~Piece() = default;

        //Getters
        std::string getTerminalSprite();
        Coordinates getCoordinates();
        double getValue();
        virtual PieceType getType()const=0;
        virtual std::vector<Coordinates>& getVectMove()=0;

        //Modèles de mouvement/capture
        virtual bool canMovePattern(Coordinates) = 0;
        virtual bool canEatPattern(Coordinates) = 0;

        //Nombre de Mouvements
        int howManyMoves();
        void incrementNbOfMoves();
        void decrementNbOfMoves();

        //Déplacement
        void moveTo(int, int);
        void moveTo(Coordinates);
};


#endif