#ifndef GAME_CONTROLLER_HPP
#define GAME_CONTROLLER_HPP

#include "player.hpp"
#include "movehistory.hpp"
#include "position_key.hpp"
#include <string>
#include <iostream>
#include <stack>

class GameController 
{
    friend bool operator==(const GameController&,const GameController&);
    friend bool operator!=(const GameController&,const GameController&);
    private:
        std::shared_ptr<Player> current_player;
        std::shared_ptr<Player> waiting_player;
        std::shared_ptr<Piece> piece_chosen;
        Coordinates cell_chosen;
        std::vector<MoveHistory> moves;
        std::vector<PositionKey> hashHistory;
        bool waiting_promotion;

    public:
        //Constructeurs / Destructeurs
        GameController();
        ~GameController();

        //Getters
        Player& getCurrentPlayer();
        Player& getWaitingPlayer();
        Coordinates getCoordsPieceChosen() const;
        std::pair<Coordinates,Coordinates> getLastMove() const;

        //Calcul de position
        uint8_t encodePiece(PieceType type, bool isBlack) const;
        void setCase(PositionKey& key, int x, int y, uint8_t val) const;
        PositionKey computeKey() const;

        //Tours Des Joueurs
        void switchTurn();
        bool whiteTurn() const;
        bool blackTurn() const;


        //Pièce Choisie
        bool isNull() const;
        bool isChosen() const;
        void choosePiece(Coordinates);
        void choosePiece(int);
        void choosePiece(std::shared_ptr<Piece>);
        void unChoosePiece();
        std::vector<Coordinates> movesOfPieceChosen();
        int movesOfPieceChosen(Coordinates*);


        //Déplacements
        void eatPiece(std::shared_ptr<Piece>s);
        bool movePiece(Coordinates, Coordinates,bool=false);
        void unMove();

        //Vérifications & Détections
        bool isEmpty(Coordinates) const;
        bool pieceInBetween(Coordinates, Coordinates) const;
        bool pieceAllyDetection(Coordinates) const;
        bool pieceEnemyDetection(Coordinates) const;
        bool pieceDectection(Coordinates) const;
        
        bool isLegalMove(Coordinates, Coordinates);
        int countLegalMovesOfPiece(std::shared_ptr<Piece>);

        int isThreaten(Coordinates) const;
        int isChecked() const;
        bool isKingCheckedAfterMove(Coordinates, Coordinates);
        bool isRepeat() const;
        bool isDraw();
        bool isPat();
        bool isCheckmate();

        //Règles Spéciales
        bool isPawnPromoted(Coordinates,bool) const;
        bool promotionPending() const;
        void promoteTo(std::shared_ptr<Piece>,PieceType);
        
        bool isMoveRock(Coordinates, Coordinates) const;
        bool canRock(Coordinates, Coordinates) const;
        Coordinates rock(Coordinates);

        bool isMoveEnPassant(Coordinates, Coordinates) const;
        bool canEnPassant(Coordinates, Coordinates) const;
        void enPassant(Coordinates, Coordinates);

};


#endif
