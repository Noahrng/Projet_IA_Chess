#ifndef TERMINAL_DISPLAY_HPP
#define TERMINAL_DISPLAY_HPP

#include "display.hpp"
#include "player.hpp"

class TerminalDisplay : public Display{
    private: 
    public:
        //Constructeur
        TerminalDisplay(GameController&, bool);
        
        //Entrée Joueur
        std::string enterPlayerCoordinates(); 

        //Test sur entrée du joueur
        bool isGameQuitted(std::string);
        bool moveCancelled(std::string);

        //Affichage du terminal
        void printBoard();
        void clearTerminal();


        //Exécution du jeu
        void run();
};

#endif