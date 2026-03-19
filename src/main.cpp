#include "game_controller.hpp"
#include "pawn.hpp"
#include "terminal_display.hpp"
#include "graphic_display.hpp"
#include "evaluator.hpp"

#include <chrono>

int main(){
    GameController play;
    Evaluator evalt(play);

    int count=0;
    auto start=std::chrono::high_resolution_clock::now();
    auto end =start+std::chrono::seconds(1);

    while(std::chrono::high_resolution_clock::now() < end)
    {
        evalt.evaluate();
        count++;
    }

    std::cout << "evaluate() appelé " << count << " fois en 1 seconde\n";



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