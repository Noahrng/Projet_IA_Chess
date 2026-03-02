#include "../include/rook.hpp"

Rook::Rook(bool col,Coordinates c): Piece(col,c,5.0/39.0,"♜")
{
    position_table = 
    {{
        {{ 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0}},  // rang 8 : 7e rangée très forte
        {{ 0.05, 0.1,  0.1,  0.1,  0.1,  0.1,  0.1,  0.05}},  // 7e rangée : pénètre chez l'ennemi
        {{-0.05, 0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.05}},  // neutre
        {{-0.05, 0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.05}},  // neutre
        {{-0.05, 0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.05}},  // neutre
        {{-0.05, 0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.05}},  // neutre
        {{-0.05, 0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.05}},  // neutre
        {{ 0.0,  0.0,  0.0,  0.05, 0.05, 0.0,  0.0,  0.0}}    // colonnes centrales légèrement mieux
    }};
}

bool Rook::canMovePattern(Coordinates new_coords)
{
    if(!new_coords.onBoard()) return false;
    return (coords.distX(new_coords) == 0) != (coords.distY(new_coords) == 0);
}

bool Rook::canEatPattern(Coordinates new_coords)
{
    return canMovePattern(new_coords);
}

PieceType Rook::getType() const
{
    return PieceType::Rook;
};