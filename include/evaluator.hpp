#ifndef EVALUATOR_HPP
#define EVALUATOR_HPP

#include "game_controller.hpp"
#include <algorithm>

class Evaluator{
    private:
        GameController &game;

        static constexpr double MAX_MATERIAL = 39.0;

        double evaluateMaterial();


    public:
        Evaluator(GameController&);

        double evaluate();
};

#endif