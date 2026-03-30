#ifndef MINIMAX_HPP
#define MINIMAX_HPP

#include "game_controller.hpp"
#include "evaluator.hpp"
#include <iostream>
#include <algorithm>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <array>

struct ChessMove
{
    Coordinates from;
    Coordinates to;
    double score;

    ChessMove():
        from{Coordinates(-1,-1)},
        to{Coordinates(-1,-1)},
        score{0.0}
    {
        
    }

    ChessMove(Coordinates from,Coordinates to,double s):
        from{from},to{to},score{s}
    {

    }
};

struct PipeResult
{
    double score;
    int from_x,from_y;
    int to_x,to_y;
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
        //Constructeurs / Destructeurs
        Minimax(GameController&,Evaluator&);

        //Getters
        ChessMove getBestMoveFork();
        ChessMove getBestMoveAtDepth(int,double,double);
        ChessMove getBestMove();
        
        //Mise à Jour
        void update_depth();

        //Vérification d'état
        bool isLosingCapture(const Coordinates,const Coordinates);
        bool isLosingMove(const Coordinates,const Coordinates);

        //Tris
        void sortMoves(Coordinates*,int,const Coordinates);
        void sortMovesWithPrevious(Coordinates*,int,Coordinates,const ChessMove&);

        //Algorithmes d'IA
        double minimax(const int,const bool,double,double);
        double quiescence(double,double,const bool,int);
};

#endif