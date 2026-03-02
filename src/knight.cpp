#include "../include/knight.hpp"

Knight::Knight(bool col,Coordinates c):Piece(col,c,3.0/39.0,"♞")
{
    position_table = {{
        {{-0.5, -0.4, -0.3, -0.3, -0.3, -0.3, -0.4, -0.5}}, // bords : très mauvais
        {{-0.4, -0.2,  0.0,  0.0,  0.0,  0.0, -0.2, -0.4}}, // quasi-bord : mauvais
        {{-0.3,  0.0,  0.1,  0.15, 0.15, 0.1,  0.0, -0.3}}, // centre élargi : correct
        {{-0.3,  0.05, 0.15, 0.2,  0.2,  0.15, 0.05,-0.3}}, // centre : bon
        {{-0.3,  0.0,  0.15, 0.2,  0.2,  0.15, 0.0, -0.3}}, // centre : bon
        {{-0.3,  0.05, 0.1,  0.15, 0.15, 0.1,  0.05,-0.3}}, // centre élargi : correct
        {{-0.4, -0.2,  0.0,  0.05, 0.05, 0.0, -0.2, -0.4}}, // quasi-bord : mauvais
        {{-0.5, -0.4, -0.3, -0.3, -0.3, -0.3, -0.4, -0.5}}  // bords : très mauvais
    }};
}

bool Knight::canMovePattern(Coordinates new_coords)
{
    if(!new_coords.onBoard()) return false;

    int distx=this->coords.distX(new_coords);
    int disty=this->coords.distY(new_coords);

    if((distx==1 && disty ==2) ||(distx==2 && disty==1))
    {
        return true;
    }
    return false;
}

bool Knight::canEatPattern(Coordinates new_coords)
{
    return canMovePattern(new_coords);
}

PieceType Knight::getType() const
{
    return PieceType::Knight;
};

