#ifndef TERMINAL_DISPLAY_HPP
#define TERMINAL_DISPLAY_HPP

#include "display.hpp"
#include "player.hpp"
#include "piece_type.hpp"

class TerminalDisplay : public Display
{
    private: 
    public:
        //Constructeurs / Destructeurs
        TerminalDisplay(GameController&,Minimax&,bool);
        
        //Entrées Joueur
        std::string playerEntryString(); 

        //Vérification d'état
        bool isLetter(char);
        bool isNumber(char);
        bool isGameQuitted(std::string);
        bool moveCancelled(std::string);

        //Conversions de String
        Coordinates convertStringIntoCoords(std::string);
        PieceType convertStringIntoType(std::string);
        
        //Affichage du terminal
        void clearTerminal();
        void printBoard();
        void printInfosPromote();

        //Exécution
        void run();
};

#endif