#include <graphic_display.hpp>
GraphicDisplay::GraphicDisplay(int w,int h,const std::string &t,Player &j1, Player &j2,bool s):
    Display(j1,j2,s),
    width{w},
    height{h},
    title{t}
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(width,height,title.c_str());
    SetTargetFPS(30);
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

        BeginDrawing();
        ClearBackground(WHITE);

        DrawText("CHESS",250,250,125,BLACK);


        EndDrawing();
    }
}