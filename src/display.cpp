#include "display.hpp"

/*----------------------Constructeurs / Destructeurs----------------------*/
Display::Display(GameController &game,Minimax &robot,bool s):game(game),robot{robot},side(s){

}