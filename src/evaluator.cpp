#include "evaluator.hpp"

Evaluator::Evaluator(GameController &game):game{game}, MAX_MATERIAL{39.0},MAX_MOBILITY{50.0}
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
    
    white_score=white.getPoint();
    black_score=black.getPoint();

    return white_score-black_score;
}

double Evaluator::evaluate()
{
    double material = evaluateMaterial()/MAX_MATERIAL;
    double score = material;

    return std::clamp(score,-0.99,0.99);
}

