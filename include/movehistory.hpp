#ifndef MOVE_HISTORY_HPP
#define MOVE_HISTORY_HPP
#include "coordinates.hpp"
#include "pieces.hpp"

struct MoveHistory
{
    Coordinates from;
    Coordinates to;
    Coordinates rookRockFrom;
    std::shared_ptr<Piece> eatenPiece;
    std::shared_ptr<Piece> promotedPiece;
    std::pair<std::shared_ptr<Piece>,Coordinates> enPassantInfo;


    MoveHistory(Coordinates from,Coordinates to):from{from},
                                                to{to},
                                                rookRockFrom(Coordinates(-1,-1)),
                                                eatenPiece{nullptr},
                                                promotedPiece{nullptr},
                                                enPassantInfo{nullptr,Coordinates(-1,-1)}{}

    friend bool operator==(const MoveHistory &a,const MoveHistory &b)
    {
        if(a.from!=b.from) return false;
        if(a.to!=b.to) return false;
        return true;
    }
};

#endif