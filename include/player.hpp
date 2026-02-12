#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <pieces.hpp>
#include <vector>
#include <memory>

class Player
{
    private:
        bool color;
        std::vector<std::unique_ptr<Piece>> pieces;
    
    public:
        Player(bool color);
        ~Player()=default;

        Piece* getPiece(Coordinates);
        void addPiece(std::unique_ptr<Piece>);
        void removePiece(Coordinates);
        Piece* getPiece(Coordinates);



};

#endif