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
        Player j1;
        Player j2;
        Player *current_player;
        Piece* piece_chosen;
    public:
        GameController();
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
};

#endif