#ifndef GRAPHIC_DISPLAY_HPP
#define GRAPHIC_DISPLAY_HPP

#include "display.hpp"
#include "player.hpp"
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


class GraphicDisplay : public Display{
    private:
        int width;
        int height;
        std::string title; 
        std::map<AssetID,Image> images;
        std::map<AssetID,Texture2D> textures;
    public:
        GraphicDisplay(int,int,const std::string&,Player&, Player&, bool);
        ~GraphicDisplay();
        GraphicDisplay(const GraphicDisplay&)=delete;
        GraphicDisplay& operator=(const GraphicDisplay&)=delete;

        AssetID getAssetForPiece(const Piece&,bool);
        void addImage(AssetID,const std::string&);
        void drawAsset(AssetID,int,int,int);
        void drawPieces(int);

        std::string getCoords(int);

        void updateDimensions();
        void run();
};

#endif