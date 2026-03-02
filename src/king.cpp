#include "../include/king.hpp"

King::King(bool col,Coordinates c):Piece(col,c,1.0,"♚")
{
    position_table = 
    {{
        {{-0.3, -0.4, -0.4, -0.5, -0.5, -0.4, -0.4, -0.3}}, // centre : dangereux
        {{-0.3, -0.4, -0.4, -0.5, -0.5, -0.4, -0.4, -0.3}}, // centre : dangereux
        {{-0.3, -0.4, -0.4, -0.5, -0.5, -0.4, -0.4, -0.3}}, // centre : dangereux
        {{-0.3, -0.4, -0.4, -0.5, -0.5, -0.4, -0.4, -0.3}}, // centre : dangereux
        {{-0.2, -0.3, -0.3, -0.4, -0.4, -0.3, -0.3, -0.2}}, // moins dangereux
        {{-0.1, -0.2, -0.2, -0.2, -0.2, -0.2, -0.2, -0.1}}, // acceptable
        {{ 0.2,  0.2,  0.0,  0.0,  0.0,  0.0,  0.2,  0.2}},  // aile : roque possible
        {{ 0.2,  0.3,  0.1,  0.0,  0.0,  0.1,  0.3,  0.2}}   // cases de roque g1/c1 : très bon
    }};
}

bool King::canMovePattern(Coordinates new_coords)
{
    if(!new_coords.onBoard()) return false;

    int distx=this->coords.distX(new_coords);
    int disty=this->coords.distY(new_coords);

    if((distx<=1 && disty<=1) && coords!=new_coords)
    {
        return true;
    }

    return false;
}

bool King::canEatPattern(Coordinates new_coords)
{
    return canMovePattern(new_coords);
}

PieceType King::getType() const
{
    return PieceType::King;
};
