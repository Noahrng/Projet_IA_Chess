#ifndef GRAPHIC_DISPLAY_HPP
#define GRAPHIC_DISPLAY_HPP

#include "display.hpp"
#include "player.hpp"
#include <raylib-5.5_linux_amd64/include/raylib.h>

class GraphicDisplay : public Display{
    private:
        int width;
        int height;
        std::string title; 
    public:
        GraphicDisplay(int,int,const std::string&,Player&, Player&, bool);
        ~GraphicDisplay();

        void updateDimensions();
        void run();
};

#endif