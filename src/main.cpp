#include "game_controller.hpp"
#include "pawn.hpp"
#include "terminal_display.hpp"
#include "graphic_display.hpp"
#include "evaluator.hpp"
#include "minimax.hpp"

#include <chrono>
#include <random>
#include <cstdlib>

int main(int argc,char*argv[]){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0,7);

    std::uniform_int_distribution<> distrib_choice(0,15);

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

    count=0;
    start=std::chrono::high_resolution_clock::now();
    end=start+std::chrono::seconds(1);

    while(std::chrono::high_resolution_clock::now() < end)
    {
        play.movePiece(Coordinates(4,6),Coordinates(4,4));
        play.switchTurn();
        play.unMove();
        count++;
    }

    std::cout << "move -> unmove effectué " << count << " fois en 1 seconde\n";

    count=0;
    start=std::chrono::high_resolution_clock::now();
    end=start+std::chrono::seconds(1);

    while(std::chrono::high_resolution_clock::now() < end)
    {
        play.isCheckmate();
        count++;
    }

    std::cout << "ischeckmate " << count << " fois en 1 seconde\n";

    count=0;
    start=std::chrono::high_resolution_clock::now();
    end=start+std::chrono::seconds(1);
    Coordinates c_testget;
    std::shared_ptr<Piece> get_test;

    while(std::chrono::high_resolution_clock::now() < end)
    {
        c_testget.setXY(distrib(gen),distrib(gen));
        get_test=play.getCurrentPlayer().getPiece(c_testget);
        count++;
    }

    std::cout << "getPiece " << count << " fois en 1 seconde\n";

    count=0;
    start=std::chrono::high_resolution_clock::now();
    end=start+std::chrono::seconds(1);

    while(std::chrono::high_resolution_clock::now() < end)
    {
        play.choosePiece(distrib_choice(gen));
        auto list_move=play.movesOfPieceChosen();
        play.unChoosePiece();

        count++;
    }

    std::cout << "get random moves of pieces " << count << " fois en 1 seconde\n";

    Minimax robot(play,evalt);
    start = std::chrono::high_resolution_clock::now();
    
    robot.getBestMove();

    end=std::chrono::high_resolution_clock::now();
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