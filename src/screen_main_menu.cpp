#include "screen_main_menu.hpp"
#include "screen_chess.hpp"

MainMenuScreen::MainMenuScreen(GameController &game,int width,int height):Screen(game)
{
    playButton=std::make_unique<Button>(width/2-100,height/2,200,60,"PLAY");
    finished=false;
}

void MainMenuScreen::update()
{
    if(playButton->isClicked())
    {
        finished=true;
    }
}
void MainMenuScreen::draw()
{
    BeginDrawing();
    ClearBackground(Color{0,128,0,255});
    playButton->draw();
    EndDrawing();
}

std::unique_ptr<Screen> MainMenuScreen::nextScreen()
{
    return std::make_unique<ChessScreen>(game);
}

bool MainMenuScreen::isFinished()
{
    return finished;
}