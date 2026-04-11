#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "pieces.hpp"
#include <vector>
#include <memory>
#include <iterator>
#include <algorithm>

class Player
{
    friend bool operator==(const Player&,const Player&);
    friend bool operator!=(const Player&,const Player&);
    private:
        bool bot;
        bool color;
        std::vector<std::shared_ptr<Piece>> pieces;
        std::shared_ptr<Piece> board[8][8];
    
    public:
        //Constructeurs / Destructeurs
        Player(bool color);
        ~Player()=default;
        Player(const Player&) = delete;            
        Player& operator=(const Player&) = delete;
        Player(Player&&) = default;              
        Player& operator=(Player&&) = default;

        //Getters
        std::shared_ptr<Piece> getPiece(int, int) const;
        std::shared_ptr<Piece> getPiece(Coordinates) const;
        std::shared_ptr<Piece> getPiece(size_t) const;
        std::shared_ptr<Piece> getKing() const;
        std::shared_ptr<Piece> getQueen() const;
        Piece& getKingFast() const;
        std::vector<std::shared_ptr<Piece>>& getPieces();
        size_t nbOfPieces() const;
        bool isBot() const;

        //Setters
        void setBot(bool);

        void updateBoard(Coordinates,Coordinates);

        //Vérification d'état
        bool isPiece(std::shared_ptr<Piece>, size_t) const;
        bool isWhite() const;
        bool isBlack() const;

        //Pièces du Joueur
        void addPiece(std::shared_ptr<Piece>);
        void removePiece(Coordinates);
        void removePiece(size_t);
        void removePiece(std::shared_ptr<Piece>);
};

#endif