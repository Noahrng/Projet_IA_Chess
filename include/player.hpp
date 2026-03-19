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
        bool color;
        std::vector<std::shared_ptr<Piece>> pieces;
        std::shared_ptr<Piece> board[8][8];
        double sum_point;
    
    public:
        Player(bool color);
        ~Player()=default;
        Player(const Player&) = delete;            
        Player& operator=(const Player&) = delete;
        Player(Player&&) = default;              
        Player& operator=(Player&&) = default;

        size_t nbOfPieces();
        std::shared_ptr<Piece> getPiece(int, int);
        std::shared_ptr<Piece> getPiece(Coordinates);
        std::shared_ptr<Piece> getPieceBoard(Coordinates);
        std::shared_ptr<Piece> getPiece(size_t);
        std::vector<std::shared_ptr<Piece>>& getPieces();
        double getPoint();

        bool isPiece(std::shared_ptr<Piece>, size_t);
        bool isWhite();
        bool isBlack();
        void addPiece(std::shared_ptr<Piece>);
        void removePiece(Coordinates);
        void removePiece(size_t);

        void update(Coordinates,Coordinates);
        void update(std::shared_ptr<Piece>,Coordinates);
        


};

#endif