#ifndef GAME_CONTROLLER_HPP
#define GAME_CONTROLLER_HPP

#include "player.hpp"
#include "coordinates.hpp"
#include <string>

class GameController 
{
    private:
        Player* j1;
        Player* j2;
        Player* current_player;
    public:
        GameController(Player*, Player*);
        //Entrées joueur
        std::string enterPlayerMovement(); 

        bool isLetter(char c);
        bool isNumber(char c);
        Coordinates convertStringIntoCoords(std::string);
};

#endif