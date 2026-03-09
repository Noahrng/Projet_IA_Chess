#include "evaluator.hpp"

Evaluator::Evaluator(GameController &game):game{game}
{

}

double Evaluator::evaluateMaterial()
{
    double white_score=0.0;
    double black_score=0.0;

    Player &current = game.getCurrentPlayer();
    Player &waiting = game.getWaitingPlayer();

    Player &white = current.isWhite() ? current : waiting;
    Player &black = current.isBlack() ? current : waiting;

    for(size_t i = 0; i < white.nbOfPieces();i++)
    {
        Piece *p = white.getPiece(i);
        if(p!=nullptr && p->getType()!=PieceType::King)
        {
            white_score+=p->getValue();
        }
    }

    for(size_t i = 0; i < black.nbOfPieces();i++)
    {
        Piece *p = black.getPiece(i);
        if(p!=nullptr && p->getType()!=PieceType::King)
        {
            black_score+=p->getValue();
        }
    }

    return white_score-black_score;
}

double Evaluator::evaluate()
{
    if(game.isCheckmate())
    {
        return game.whiteTurn() ? -1.0 : 1.0;
    }

    double material = evaluateMaterial()/MAX_MATERIAL;

    return std::clamp(material,-1.0,1.0);
}

