#include <player.hpp>
Player::Player(bool color):color{color}
{
    
}
void Player::addPiece(std::unique_ptr<Piece> p){
    pieces.push_back(std::move(p));
}

void Player::removePiece(Coordinates c){
    for(std::size_t i=0;i<pieces.size();i++){
        if(pieces[i].get()->getCoordinates()==c){
            pieces.erase(pieces.begin()+i);
        }
    }
}

    