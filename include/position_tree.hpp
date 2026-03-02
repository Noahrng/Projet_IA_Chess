#ifndef POSITION_TREE_HPP
#define POSITION_TREE_HPP

#include "game_controller.hpp"
#include <vector>
#include <memory>
#include <fstream>
#include <algorithm>

struct Position
{
    // Le coup qui a mené à cette position
    Coordinates from;
    Coordinates to;

    // Score évalué de cette position (-1.0 à 1.0)
    double score;
    double eval_score;

    // Enfants : toutes les positions atteignables depuis ici
    std::vector<std::shared_ptr<Position>> children;

    // Parent : pour remonter l'arbre
    std::weak_ptr<Position> parent;

    Position(Coordinates from, Coordinates to, double score = 0.0)
        : from{from}, to{to}, score{score},eval_score{0.0}
    {}
};

class PositionTree
{
    private:
        std::shared_ptr<Position> root;
        GameController& game;

    public:
        PositionTree(GameController&);

        // Construction de l'arbre
        void build(int);
        void scanRays(Coordinates, int[][2], int, std::vector<Coordinates>&);
        std::vector<Coordinates> generateMovesForPieces(Piece *p);
        double minimax(std::shared_ptr<Position>,int,bool,double,double);

        // Getters
        std::shared_ptr<Position> getRoot();
        std::shared_ptr<Position> bestMove();

        // Debug
        void print(std::shared_ptr<Position>, int = 0);
        void printToFile(const std::string& path);
        void printToFile(std::shared_ptr<Position> node, int depth, std::ofstream& file);
};

#endif