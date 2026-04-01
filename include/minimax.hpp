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
#include <unordered_map>

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

struct TTEntry {
    double score;
    int depth;
    double alpha;
    double beta;
};

struct PositionKeyHash {
    std::size_t operator()(const PositionKey& k) const {
        std::size_t h = 0;
        for(auto v : k.data)
            h ^= std::hash<uint64_t>()(v + 0x9e3779b97f4a7c15ULL + (h<<6) + (h>>2));
        return h ^ std::hash<bool>()(k.white_turn);
    }
};

class Minimax
{
    private:
        GameController &game;
        Evaluator &eval;
        int minimax_depth;
        int quiescence_depth;
        ChessMove previous_best;
        std::unordered_map<PositionKey, TTEntry, PositionKeyHash> TT;
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