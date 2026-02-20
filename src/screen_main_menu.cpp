#include "screen_main_menu.hpp"
#include "screen_chess.hpp"

MainMenuScreen::MainMenuScreen(GameController &game,int width,int height):Screen(game)
{
    playButton=std::make_unique<Button>(width/2-100,height/2,200,60,"PLAY");
    title=std::make_unique<TextBox>(width/2-100,height/8,200,60,"Bienvenu sur notre jeux d'echec fait maison");
    title->setBackgroundColor(Color{0,128,128,255});
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
    title->draw();
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