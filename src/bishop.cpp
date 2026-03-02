#include "../include/bishop.hpp"

Bishop::Bishop(bool col,Coordinates c): Piece(col,c,3.0/39.0,"♝")
{
    position_table = 
    {{
        {{-0.2, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.2}}, // bords : mauvais
        {{-0.1,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.1}}, // quasi-bord : neutre
        {{-0.1,  0.0,  0.05, 0.1,  0.1,  0.05, 0.0, -0.1}}, // diagonales actives
        {{-0.1,  0.05, 0.05, 0.1,  0.1,  0.05, 0.05,-0.1}}, // centre : bon
        {{-0.1,  0.0,  0.1,  0.1,  0.1,  0.1,  0.0, -0.1}}, // centre : bon
        {{-0.1,  0.1,  0.1,  0.1,  0.1,  0.1,  0.1, -0.1}}, // diagonales longues
        {{-0.1,  0.05, 0.0,  0.0,  0.0,  0.0,  0.05,-0.1}}, // développement normal
        {{-0.2, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.2}}  // bords : mauvais
    }};
}

bool Bishop::canMovePattern(Coordinates new_coords)
{
    if(!new_coords.onBoard()) return false;
    return coords.distX(new_coords) == coords.distY(new_coords) && coords != new_coords;
}

bool Bishop::canEatPattern(Coordinates new_coords)
{
    return canMovePattern(new_coords);
}

PieceType Bishop::getType() const
{
    return PieceType::Bishop;
}