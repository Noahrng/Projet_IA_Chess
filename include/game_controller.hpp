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
        //Constructeurs / Destructeurs
        GameController();
        ~GameController();

        //Getters
        Player& getCurrentPlayer();
        Player& getWaitingPlayer();
        Coordinates getCoordsPieceChosen();

        //Tours Des Joueurs
        void switchTurn();
        bool whiteTurn();
        bool blackTurn();


        //Pièce Choisie
        bool isNull();
        bool isChosen();
        void choosePiece(Coordinates);
        void unChoosePiece();
        std::vector<Coordinates> movesOfPieceChosen();


        //Déplacements
        void eatPiece(std::shared_ptr<Piece>s);
        bool movePiece(Coordinates, Coordinates);
        void unMove();

        //Vérifications & Détections
        bool isEmpty(Coordinates);
        bool pieceInBetween(Coordinates, Coordinates);
        bool pieceAllyDetection(Coordinates);
        bool pieceEnemyDetection(Coordinates);
        bool pieceDectection(Coordinates);
        
        bool isLegalMove(Coordinates, Coordinates);
        int countLegalMovesOfPiece(std::shared_ptr<Piece>);

        int isThreaten(Coordinates);
        int isChecked();
        bool isKingCheckedAfterMove(Coordinates, Coordinates);
        bool isCheckmate();

        //Règles Spéciales
        bool isPawnPromoted(Coordinates,bool);
        bool promotionPending();
        void promoteTo(std::shared_ptr<Piece>,PieceType);
        
        bool isMoveRock(Coordinates, Coordinates);
        bool canRock(Coordinates, Coordinates);
        void rock(Coordinates);

        bool isMoveEnPassant(Coordinates, Coordinates);
        bool canEnPassant(Coordinates, Coordinates);
        void enPassant(Coordinates, Coordinates);

};


#endif
