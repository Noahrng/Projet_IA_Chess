#ifndef GRAPHIC_DISPLAY_HPP
#define GRAPHIC_DISPLAY_HPP

#include "display.hpp"
#include "player.hpp"
#include "screen.hpp"
#include "screen_main_menu.hpp"
#include "screen_chess.hpp"
#include <raylib-5.5_linux_amd64/include/raylib.h>
#include <memory>

class GraphicDisplay : public Display{
    private:
        int width;
        int height;
        std::string title; 
        std::unique_ptr<Screen> currentScreen;
    public:
        GraphicDisplay(int,int,const std::string&,GameController&,bool);
        ~GraphicDisplay();
        GraphicDisplay(const GraphicDisplay&)=delete;
        GraphicDisplay& operator=(const GraphicDisplay&)=delete;

        void updateDimensions();
        void run();
};

#endif