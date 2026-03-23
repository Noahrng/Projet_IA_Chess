#include "game_controller.hpp"
#include "pawn.hpp"
#include "terminal_display.hpp"
#include "graphic_display.hpp"
#include "evaluator.hpp"
#include "minimax.hpp"

#include <chrono>
#include <random>
#include <cstdlib>

int main(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0,7);

    std::uniform_int_distribution<> distrib_choice(0,15);

    GameController play;
    Evaluator evalt(play);
    Minimax robot(play,evalt,5,2);
    auto start = std::chrono::high_resolution_clock::now();
    
    robot.getBestMove();

    auto end=std::chrono::high_resolution_clock::now();
    auto duration=std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
    std::cout << "Temps : " << duration.count() << " ms" << std::endl;
    
    std::cout<<evalt.evaluate()<<"\n";


    std::cout << "Affichage Terminal (0) ou Interface Graphique (1) ?\n";
    bool affichage;
    std::cin >> affichage;

    

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