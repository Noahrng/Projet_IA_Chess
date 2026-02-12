#include <player.hpp>
Player::Player(bool color):color{color}
{
    
}
void Player::addPiece(std::unique_ptr<Piece> p){
    pieces.push_back(std::move(p));
}

void Player::removePiece(Coordinates c){
    std::size_t i=0;
    while(i<pieces.size() && pieces[i].get()->getCoordinates()!=c){
        i++;
    }
    pieces.erase(pieces.begin()+i);
}

    