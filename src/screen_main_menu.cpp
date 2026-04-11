#include "screen_main_menu.hpp"
#include "screen_chess.hpp"

/*----------------------Constructeurs / Destructeurs----------------------*/
MainMenuScreen::MainMenuScreen(GameController &game,Minimax &robot,int width,int height):Screen(game,robot)
{

    playButton=std::make_unique<Button>(
        std::make_unique<CircleShape>(width/2-100,height/2,100),
        "PLAY"
    );

    playButton->setNormalColor(YELLOW);

    title = std::make_unique<TextShape>(
        std::make_unique<CircleShape>(width/2-300,200,150),
        "Bienvenue sur notre jeu d'échecs"
    );

    title->setTextColor(WHITE);
    finished=false;
}

/*--------------------------Vérification d'État---------------------------*/
bool MainMenuScreen::isFinished()
/*
    Description:
        Renvoie si l'ecran courant est terminer
*/
{
    return finished;
}

/*------------------------------Mise à Jour-------------------------------*/
void MainMenuScreen::update()
/*
    Description:
        Actualise les paramètre en fonction d'input utilisateur
*/
{
    if(playButton->isClicked())
    {
        finished=true;
    }
}

std::unique_ptr<Screen> MainMenuScreen::nextScreen()
/*
    Description:
        Renvoie la prochaine instance de screen après le screen courant
*/
{
    return std::make_unique<ChessScreen>(game,robot);
}

/*-------------------------Dessiner le Main Menu--------------------------*/
void MainMenuScreen::draw()
/*
    Description:
        Affichage
*/
{
    BeginDrawing();
    ClearBackground(Color{0,128,0,255});
    playButton->draw();
    title->draw();
    EndDrawing();
}