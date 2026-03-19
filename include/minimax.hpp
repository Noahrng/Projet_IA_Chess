#ifndef MINIMAX_HPP
#define MINIMAX_HPP

#include "game_controller.hpp"
#include "evaluator.hpp"
#include <iostream>
#include <algorithm>
#include <chrono>

struct ChessMove
{
    Coordinates from;
    Coordinates to;
    double score;

    ChessMove():
        from{Coordinates(-1,-1)},
        to{Coordinates(-1,-1)},
        score{0.0}
    {}

    ChessMove(Coordinates from,Coordinates to,double s):
        from{from},to{to},score{s}
    {}
};

class Minimax
{
    private:
        GameController &game;
        Evaluator &eval;
        size_t nb_node;
        std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
    public:
        Minimax(GameController&,Evaluator&);

        void sortMoves(std::vector<Coordinates>&,Coordinates);

        double minimax(int,bool,double,double);
        double quiescence(double,double,bool,int);
        ChessMove getBestMove();
};

#endif