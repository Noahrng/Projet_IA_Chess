#include <graphic_display.hpp>
GraphicDisplay::GraphicDisplay(int w,int h,const std::string &t,GameController& game,bool s):
    Display(game,s),
    width{w},
    height{h},
    title{t},
    currentScreen{std::make_unique<MainMenuScreen>(game,width,height)}
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(width,height,title.c_str());
    SetTargetFPS(30);
    SetExitKey(KEY_ESCAPE);

}

GraphicDisplay::~GraphicDisplay(){
    CloseWindow();
}

void GraphicDisplay::updateDimensions()
{
    width=GetScreenWidth();
    height=GetScreenHeight();
}

void GraphicDisplay::run()
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