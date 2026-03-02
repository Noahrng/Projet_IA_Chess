#include <game_controller.hpp>
#include <pawn.hpp>
#include "terminal_display.hpp"
#include <graphic_display.hpp>
#include "position_tree.hpp"

int main(){
    GameController play;

    Coordinates t(1,-1);
    Coordinates t2(-t);

    std::cout<<t<<" "<<t2<<"\n";

    t2=t2*4;

    std::cout<<t2<<"\n";
    PositionTree pt(play);

    pt.build(3);
    //pt.print(pt.getRoot(),1);
    pt.printToFile("moves.txt");


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