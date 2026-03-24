#ifndef MINIMAX_HPP
#define MINIMAX_HPP

#include "game_controller.hpp"
#include "evaluator.hpp"
#include <iostream>
#include <algorithm>

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
        int minimax_depth;
        int quiescence_depth;

        ChessMove previous_best;

        
    public:
        Minimax(GameController&,Evaluator&,int,int);
        void update_depth();

        bool isLosingCapture(Coordinates from, Coordinates to);
        double minimax(int,bool,double,double);
        double quiescence(double,double,bool,int);
        void sortMoves(std::vector<Coordinates>&,Coordinates);
        void sortMovesWithPrevious(std::vector<Coordinates>&,Coordinates,const ChessMove&);
        ChessMove getBestMoveAtDepth(int,double,double);
        ChessMove getBestMove();
};

#endif