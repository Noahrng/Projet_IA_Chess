#ifndef GAME_CONTROLLER_HPP
#define GAME_CONTROLLER_HPP

#include "player.hpp"
#include "coordinates.hpp"
#include <string>
#include <iostream>

class GameController 
{
    friend bool operator==(const GameController&,const GameController&);
    friend bool operator!=(const GameController&,const GameController&);
    private:
        Player* current_player;
        Player* waiting_player;
        Piece* piece_chosen;
    public:
        GameController();
        ~GameController();
        //Entrées joueur

        
        std::string enterPlayerCoordinates(); 
        void choosePiece(Coordinates);
        void switchTurn();

        Player& getJ1();
        Player& getJ2();

        bool isLetter(char c);
        bool isNumber(char c);
        bool isNull();
        Coordinates convertStringIntoCoords(std::string);

        //Déplacements
        void mangerPiece(Piece * p);
        void movePiece(Coordinates from, Coordinates to);

        //detection
        bool pieceInBetween(Coordinates from, Coordinates to);
        bool canMovePiece(Coordinates, Coordinates);
        bool pieceDetectionAlly(Coordinates);
        bool pieceDetectionEnemy(Coordinates);
};


#endif