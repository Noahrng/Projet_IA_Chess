#ifndef SCREEN_CHESS_HPP
#define SCREEN_CHESS_HPP

#include "screen.hpp"
#include "game_asset.hpp"
#include "game_controller.hpp"
#include <map>
#include <memory>
#include <cstdlib>

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
        //Constructeurs / Destructeurs
        ChessScreen(GameController&,Minimax&);
        ~ChessScreen();

        //Getters
        AssetID getAssetForPiece(const Piece&,bool);
        AssetID getAssetForPiece(const PieceType&,bool);
        Coordinates getCoords(int);

        //Vérification d'État
        bool isFinished() override;

        //Mise à Jour
        void update() override;
        std::unique_ptr<Screen> nextScreen() override;

        //Action du Joueur
        void scrollPiece(Coordinates,int);
        void switchSide();

        //Texture
        void addImage(AssetID,const std::string&);
        
        //Dessiner le Jeu
        void drawAsset(AssetID,int,int,int,Color=WHITE);
        void drawPieces(int,Coordinates={-1,-1});
        void drawCircles(int,std::vector<Coordinates>);
        void draw() override;
};

#endif