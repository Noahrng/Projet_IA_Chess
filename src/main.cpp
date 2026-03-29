#include "game_controller.hpp"
#include "terminal_display.hpp"
#include "graphic_display.hpp"
#include "minimax.hpp"

#include <chrono>
#include <cstdlib>

int main(){
    GameController play;
    Evaluator evalt(play);
    Minimax robot(play,evalt);

    auto start = std::chrono::high_resolution_clock::now();
    robot.getBestMoveFork();
    auto end=std::chrono::high_resolution_clock::now();
    auto duration=std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
    std::cout << "Temps : " << duration.count() << " ms" << std::endl;
    
    std::cout << "Affichage Terminal (0) ou Interface Graphique (1) ?\n";
    bool affichage;
    std::cin >> affichage;

    std::cout<<"Voulez vous jouez contre une IA (0:non) (1:oui) (2:IA vs IA)"<<std::endl;
    int isAI;
    std::cin>>isAI;

    if(isAI==2)
    {
        play.getWaitingPlayer().setBot(true);
        play.getCurrentPlayer().setBot(true);
    }
    else if(isAI)
    {
        std::cout<<"Voulez vous jouez les blanc ? (0:non) (1:oui)"<<std::endl;
        int white;
        std::cin>>white;
        if(white)
            play.getWaitingPlayer().setBot(true);
        else
            play.getCurrentPlayer().setBot(true);
    }

    

    if(!affichage)
    {
        TerminalDisplay t(play,robot,0);
        t.run();
    }

    else
    {
        GraphicDisplay gp1(900,900,"CHESS",play,robot,0);
        gp1.run();
    }   
    
    return 0;
}