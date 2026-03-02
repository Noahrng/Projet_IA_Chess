#include "../include/queen.hpp"
#include "../include/bishop.hpp"
#include "../include/rook.hpp"

Queen::Queen(bool col,Coordinates c): Piece(col,c,9.0/39.0,"♛")
{
    position_table = 
    {{
        {{-0.2, -0.1, -0.1, -0.05,-0.05,-0.1, -0.1, -0.2}}, // bords : mauvais
        {{-0.1,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.1}}, // neutre
        {{-0.1,  0.0,  0.05, 0.05, 0.05, 0.05, 0.0, -0.1}}, // légèrement mieux
        {{-0.05, 0.0,  0.05, 0.05, 0.05, 0.05, 0.0, -0.05}},// centre : bon
        {{ 0.0,  0.0,  0.05, 0.05, 0.05, 0.05, 0.0, -0.05}},// centre : bon
        {{-0.1,  0.05, 0.05, 0.05, 0.05, 0.05, 0.0, -0.1}}, // légèrement mieux
        {{-0.1,  0.0,  0.05, 0.0,  0.0,  0.0,  0.0, -0.1}}, // développement prudent
        {{-0.2, -0.1, -0.1, -0.05,-0.05,-0.1, -0.1, -0.2}}  // bords : mauvais
    }};
}

bool Queen::canMovePattern(Coordinates new_coords){
    if(!new_coords.onBoard()) return false;

    Bishop b(color, coords);
    Rook r(color, coords);

    return b.canMovePattern(new_coords) || r.canMovePattern(new_coords);
}

bool Queen::canEatPattern(Coordinates new_coords)
{
    return canMovePattern(new_coords);
}

PieceType Queen::getType() const
{
    return PieceType::Queen;
};