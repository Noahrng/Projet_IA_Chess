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
        Coordinates cell_chosen;
    public:
        GameController();
        ~GameController();
        //Entrées joueur

        
        std::string enterPlayerCoordinates(); 
        bool moveCancelled(std::string s);
        void choosePiece(Coordinates);
        void switchTurn();

        Player& getCurrentPlayer();
        Player& getWaitingPlayer();
        Coordinates getCoordsPieceChosen();

        bool isLetter(char c);
        bool isNumber(char c);
        bool isNull();
        Coordinates convertStringIntoCoords(std::string);
        bool whiteTurn();
        bool blackTurn();

        //Déplacements
        void eatPiece(Piece * p);
        bool movePiece(Coordinates from, Coordinates to);
        void promoteTo(Piece*, PieceType t);

        //detection
        bool isPromoted(Coordinates c,bool);
        bool pieceInBetween(Coordinates from, Coordinates to);
        bool canMovePiece(Coordinates, Coordinates, bool);
        bool pieceAllyDetection(Coordinates);
        bool pieceEnemyDetection(Coordinates);
        int isThreaten(Coordinates c);
        int isChecked();
};


#endif