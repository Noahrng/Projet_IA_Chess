#ifndef EVALUATOR_HPP
#define EVALUATOR_HPP

#include "game_controller.hpp"
#include <algorithm>

class Evaluator
{
    private:
        GameController &game;

    public:
        Evaluator(GameController&);

        double evaluate();
        double evaluateMaterial();
        double evaluatePosition();
        double evaluateMobility();
};

#endif