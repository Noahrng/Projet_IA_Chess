#ifndef SCREEN_CHESS_HPP
#define SCREEN_CHESS_HPP

#include "screen.hpp"
#include "game_controller.hpp"
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

class ChessScreen : public Screen
{
    private:
        bool side;
        bool finished;
        std::map<AssetID,Image> images;
        std::map<AssetID,Texture2D> textures;

        

    public:
        ChessScreen(GameController&);
        ~ChessScreen();

        
        void drawAsset(AssetID,int,int,int);
        void drawPieces(int);

        void addImage(AssetID,const std::string&);

        AssetID getAssetForPiece(const Piece&,bool);
        std::string getCoords(int);

        void switchSide();

        void update() override;
        void draw() override;

        bool isFinished() override;
        std::unique_ptr<Screen> nextScreen() override;
};

#endif