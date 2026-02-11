#include "../include/queen.hpp"
#include "../include/bishop.hpp"
#include "../include/rook.hpp"

Queen::Queen(bool col,Coordinates c): Piece(col,c){}

bool Queen::canMove(Coordinates new_coords){
    Bishop b(color, coords);
    Rook r(color, coords);

    return b.canMove(new_coords) || r.canMove(new_coords);
}