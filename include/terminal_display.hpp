#ifndef TERMINAL_DISPLAY_HPP
#define TERMINAL_DISPLAY_HPP

#include "display.hpp"
#include "player.hpp"
#include "piece_type.hpp"

class TerminalDisplay : public Display{
    private: 
    public:
        //Constructeur
        TerminalDisplay(GameController&, bool);
        
        //Entrée Joueur
        std::string playerEntryString(); 

        //Test sur entrée du joueur
        bool isLetter(char);
        bool isNumber(char);
        bool isGameQuitted(std::string);
        bool moveCancelled(std::string);

        //Conversions de String
        Coordinates convertStringIntoCoords(std::string);
        PieceType convertStringIntoType(std::string);
        
        //Affichage du terminal
        void printBoard();
        void clearTerminal();
        void printInfosPromote();

        //Exécution du jeu
        void run();
};

#endif