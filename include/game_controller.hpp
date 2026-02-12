#ifndef GAME_CONTROLLER_HPP
#define GAME_CONTROLLER_HPP

#include "player.hpp"
#include "coordinates.hpp"
#include <string>
#include <iostream>

class GameController 
{
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

        bool isLetter(char c);
        bool isNumber(char c);
        bool isnull();
        Coordinates convertStringIntoCoords(std::string);
};

#endif