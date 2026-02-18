#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "pieces.hpp"
#include <vector>
#include <memory>

class Player
{
    friend bool operator==(const Player&,const Player&);
    friend bool operator!=(const Player&,const Player&);
    private:
        bool color;
        std::vector<std::unique_ptr<Piece>> pieces;
    
    public:
        Player(bool color);
        ~Player()=default;
        Player(const Player&) = delete;            
        Player& operator=(const Player&) = delete;
        Player(Player&&) = default;              
        Player& operator=(Player&&) = default;

        size_t nbOfPieces();
        Piece* getPiece(Coordinates);
        bool isPiece(Piece*, size_t);
        bool isWhite();
        bool isBlack();
        void addPiece(std::unique_ptr<Piece>);
        void removePiece(Coordinates);
        void removePiece(size_t);
        


};

#endif