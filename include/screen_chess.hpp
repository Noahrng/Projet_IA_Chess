#ifndef SCREEN_CHESS_HPP
#define SCREEN_CHESS_HPP

#include "screen.hpp"
#include "game_asset.hpp"
#include "game_controller.hpp"
#include <map>
#include <memory>

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
        std::map<AssetID,std::unique_ptr<GameAsset>> images;
        Coordinates promoted;
        bool color;

    public:
        ChessScreen(GameController&);
        ~ChessScreen();

        void scrollPiece(Coordinates,int);
        
        void drawAsset(AssetID,int,int,int,Color=WHITE);
        void drawPieces(int,Coordinates={-1,-1});
        void drawCircles(int,std::vector<Coordinates>);

        void addImage(AssetID,const std::string&);

        AssetID getAssetForPiece(const Piece&,bool);
        AssetID getAssetForPiece(const PieceType&,bool);
        Coordinates getCoords(int);

        void switchSide();

        void update() override;
        void draw() override;

        bool isFinished() override;
        std::unique_ptr<Screen> nextScreen() override;
};

#endif