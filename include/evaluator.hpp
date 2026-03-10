#ifndef EVALUATOR_HPP
#define EVALUATOR_HPP

#include "game_controller.hpp"
#include <algorithm>

class Evaluator{
    private:
        GameController &game;

        const double MAX_MATERIAL;
        const double MAX_MOBILITY;

        double evaluateMaterial();
        double evaluateMobility();


    public:
        Evaluator(GameController&);

        double evaluate();
};

#endif