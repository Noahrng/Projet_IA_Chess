#ifndef GRAPHIC_DISPLAY_HPP
#define GRAPHIC_DISPLAY_HPP

#include "display.hpp"
#include "player.hpp"
#include "button.hpp"
#include <raylib-5.5_linux_amd64/include/raylib.h>
#include <map>

enum class AssetID
{
    pawnWhite=0,
    pawnBlack,
    rookWhite,
    rookBlack,
    knightWhite,
    knightBlack,
    bishopWhite,
    bishopBlack,
    queenWhite,
    queenBlack,
    kingWhite,
    kingBlack,
    chessBoard
};

enum class ButtonID{
    PlayButton,
    Option
};

enum class State{
    MainMenu,
    Game
};

class GraphicDisplay : public Display{
    private:
        int width;
        int height;
        State etat;
        std::string title; 
        std::map<AssetID,Image> images;
        std::map<AssetID,Texture2D> textures;
        std::map<ButtonID,Button> buttons;
    public:
        GraphicDisplay(int,int,const std::string&,GameController&,bool);
        ~GraphicDisplay();
        GraphicDisplay(const GraphicDisplay&)=delete;
        GraphicDisplay& operator=(const GraphicDisplay&)=delete;

        void addImage(AssetID,const std::string&);
        void addButton(ButtonID,const std::string&,float,float,float,float);

        
        
        void drawAsset(AssetID,int,int,int);
        void drawPieces(int);
        void drawChess();
        void drawMainMenu();

        void switchSide();

        void goToMainMenu();
        void goToChess();

        AssetID getAssetForPiece(const Piece&,bool);
        Button& getButtonForId(ButtonID);
        std::string getCoords(int);

        void updateDimensions();
        void run();
};

#endif