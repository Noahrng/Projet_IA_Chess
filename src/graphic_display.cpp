#include <graphic_display.hpp>

/*----------------------Constructeurs / Destructeurs----------------------*/
GraphicDisplay::GraphicDisplay(int w,int h,const std::string &t,GameController& game,Minimax &robot,bool s):
    Display(game,robot,s),
    width{w},
    height{h},
    title{t},
    currentScreen{std::make_unique<MainMenuScreen>(game,robot,width,height)}
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(width,height,title.c_str());
    SetTargetFPS(30);
    SetExitKey(KEY_ESCAPE);

}

GraphicDisplay::~GraphicDisplay(){
    currentScreen.reset();
    CloseWindow();
}

/*------------------------------Mise à Jour-------------------------------*/
void GraphicDisplay::updateDimensions()
/*
    Description:
        Actualise les dimension de la fenetre
*/
{
    width=GetScreenWidth();
    height=GetScreenHeight();
}

/*-------------------------------Exécution--------------------------------*/
void GraphicDisplay::run()
/*
    Description:
        Boucle d'execution de l'interface graphique
*/
{
    while(!WindowShouldClose())
    {
        if(IsWindowResized())
        {
            updateDimensions();
        }
        
        currentScreen->update();
        currentScreen->draw();

        if(currentScreen->isFinished())
        {
            currentScreen=currentScreen->nextScreen();
        }
    }
}