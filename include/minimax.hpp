#ifndef MINIMAX_HPP
#define MINIMAX_HPP

#include "game_controller.hpp"
#include "evaluator.hpp"
#include <iostream>
#include <algorithm>
#include <chrono>

class Minimax
{
    private:
        GameController &game;
        Evaluator &eval;
        size_t nb_node;
        std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
    public:
        Minimax(GameController&,Evaluator&);

        double minimax(int,bool,double,double);
};

#endif