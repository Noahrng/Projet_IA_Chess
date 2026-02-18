#ifndef SCREEN_MAIN_MENU
#define SCREEN_MAIN_MENU

#include "screen.hpp"
#include <vector>
#include <memory>


class MainMenuScreen : public Screen
{
    private:
        std::unique_ptr<Button> playButton;
        bool finished;
    public:
        MainMenuScreen(GameController&,int width,int height);

        void update() override;
        void draw() override;

        bool isFinished() override;
        std::unique_ptr<Screen> nextScreen() override;
};

#endif