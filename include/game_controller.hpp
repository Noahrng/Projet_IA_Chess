#ifndef GAME_CONTROLLER_HPP
#define GAME_CONTROLLER_HPP

#include "player.hpp"
#include "coordinates.hpp"
#include <string>
#include <iostream>
#include <stack>

struct MoveHistory
{
    Coordinates from;
    Coordinates to;
    std::shared_ptr<Piece> eatenPiece;
    std::shared_ptr<Piece> promotedPiece;
};

class GameController 
{
    friend bool operator==(const GameController&,const GameController&);
    friend bool operator!=(const GameController&,const GameController&);
    private:
        std::shared_ptr<Player> current_player;
        std::shared_ptr<Player> waiting_player;
        std::shared_ptr<Piece> piece_chosen;
        Coordinates cell_chosen;
        bool waiting_promotion;
        std::stack<MoveHistory> moves;

    public:
        GameController();
        ~GameController();
        //Entrées joueur

        
        void switchTurn();

        Player& getCurrentPlayer();
        Player& getWaitingPlayer();
        Coordinates getCoordsPieceChosen();

        bool isLetter(char c);
        bool isNumber(char c);
        bool isNull();
        Coordinates convertStringIntoCoords(std::string);
        bool whiteTurn();
        bool blackTurn();

        //Déplacements
        void eatPiece(std::shared_ptr<Piece> p);
        bool movePiece(Coordinates from, Coordinates to);
        void promoteTo(std::shared_ptr<Piece>,PieceType t);

        //Pièces choisies
        void choosePiece(Coordinates);
        void unChoosePiece();
        bool isChosen();
        std::vector<Coordinates> movesOfPieceChosen();
        void unMove();

        int CountMovesOfPiece(std::shared_ptr<Piece>);

        //detection
        bool isPawnPromoted(Coordinates c,bool);
        bool promotionPending();
        bool pieceInBetween(Coordinates from, Coordinates to);
        bool isLegalMove(Coordinates, Coordinates);
        bool isEmpty(Coordinates);
        bool pieceAllyDetection(Coordinates);
        bool pieceEnemyDetection(Coordinates);
        bool pieceDectection(Coordinates);
        int isThreaten(Coordinates c);
        int isChecked();
        bool isKingCheckedAfterMove(Coordinates, Coordinates);
        bool isCheckmate();
};


#endif