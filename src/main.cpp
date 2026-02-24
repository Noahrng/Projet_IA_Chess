#include <game_controller.hpp>
#include <pawn.hpp>
#include "terminal_display.hpp"
#include <graphic_display.hpp>

int main(){
    GameController play;

    std::cout << "Affichage Terminal (0) ou Interface Graphique (1) ?\n";
    bool affichage;
    std::cin >> affichage;

    if(!affichage)
    {
        TerminalDisplay t(play,0);
        t.run();
    }

    else
    {
        GraphicDisplay gp1(900,900,"CHESS",play,0);
        gp1.run();
    }   
    
    return 0;
}