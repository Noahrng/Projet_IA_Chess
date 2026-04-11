#ifndef GRAPHIC_DISPLAY_HPP
#define GRAPHIC_DISPLAY_HPP

#include "display.hpp"
#include "player.hpp"
#include "screen.hpp"
#include "screen_main_menu.hpp"
#include <raylib.h>
#include <memory>

class GraphicDisplay : public Display{
    private:
        int width;
        int height;
        std::string title; 
        std::unique_ptr<Screen> currentScreen;
    public:
        //Constructeurs / Destructeurs
        GraphicDisplay(int,int,const std::string&,GameController&,Minimax&,bool);
        ~GraphicDisplay();
        GraphicDisplay(const GraphicDisplay&)=delete;
        GraphicDisplay& operator=(const GraphicDisplay&)=delete;

        //Mise à Jour
        void updateDimensions();

        //Exécution
        void run();
};

#endif