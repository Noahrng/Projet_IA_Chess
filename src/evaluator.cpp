#include "evaluator.hpp"

Evaluator::Evaluator(GameController &game):game{game}, MAX_MATERIAL{39.0},MAX_MOBILITY{50.0}
{

}

double Evaluator::evaluateMaterial()
{
    Player &current = game.getCurrentPlayer();
    Player &waiting = game.getWaitingPlayer();

    Player &white = current.isWhite() ? current : waiting;
    Player &black = current.isBlack() ? current : waiting;
    return white.getPoint() - black.getPoint();
}

double Evaluator::evaluate()
{
    double material = evaluateMaterial()/MAX_MATERIAL;

    double score = material;

    return std::clamp(score,-0.99,0.99);
}

