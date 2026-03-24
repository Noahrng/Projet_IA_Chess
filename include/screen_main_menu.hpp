#ifndef SCREEN_MAIN_MENU
#define SCREEN_MAIN_MENU

#include "screen.hpp"
#include "button.hpp"
#include "text_shape.hpp"
#include "rectangle_shape.hpp"
#include "circle_shape.hpp"
#include <memory>


class MainMenuScreen : public Screen
{
    private:
        std::unique_ptr<Button> playButton;
        std::unique_ptr<TextShape> title;
        bool finished;
    public:
        //Constructeurs / Destructeurs
        MainMenuScreen(GameController&,Minimax&,int width,int height);

        //Vérification d'État
        bool isFinished() override;

        //Mise à Jour
        void update() override;
        std::unique_ptr<Screen> nextScreen() override;

        //Dessiner le Main Menu
        void draw() override;

};

#endif