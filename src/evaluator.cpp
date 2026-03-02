#include "evaluator.hpp"

Evaluator::Evaluator(GameController &game):game{game}
{

}

double Evaluator::evaluateMaterial()
{
    double score=0.0;

    for(size_t  i = 0;i<game.getCurrentPlayer().nbOfPieces();i++)
    {
        score+=game.getCurrentPlayer().getPiece(i)->getValue();
    }

    for(size_t  i = 0;i<game.getWaitingPlayer().nbOfPieces();i++)
    {
        score-=game.getWaitingPlayer().getPiece(i)->getValue();
    }

    return std::clamp(score,-1.0,1.0);
}

double Evaluator::evaluatePosition()
{
    double score=0.0;

    for(size_t  i = 0;i<game.getCurrentPlayer().nbOfPieces();i++)
    {
        score+=game.getCurrentPlayer().getPiece(i)->getPositionBonus();
    }

    for(size_t  i = 0;i<game.getWaitingPlayer().nbOfPieces();i++)
    {
        score-=game.getWaitingPlayer().getPiece(i)->getPositionBonus();
    }

    return std::clamp(score,-1.0,1.0);
}

double Evaluator::evaluate()
{
    double mat=evaluateMaterial()*0.8;
    double pos=evaluatePosition()*0.2;

    return std::clamp(mat+pos,-1.0,1.0);
}