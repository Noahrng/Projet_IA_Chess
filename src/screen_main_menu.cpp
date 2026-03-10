#include "screen_main_menu.hpp"
#include "screen_chess.hpp"

MainMenuScreen::MainMenuScreen(GameController &game,int width,int height):Screen(game)
{

    playButton=std::make_unique<Button>(
        std::make_unique<CircleShape>(width/2-100,height/2,100),
        "PLAY"
    );

    playButton->SetnormalColor(YELLOW);

    title = std::make_unique<TextShape>(
        std::make_unique<RectangleShape>(width/2-300,50,400,120),
        "Bienvenue sur notre jeu d'échecs"
    );

    title->setTextColor(WHITE);
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