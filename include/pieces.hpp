#ifndef PIECES_HPP
#define PIECES_HPP
#include <plateau.hpp>
#include <vector>

class Piece  {
    private:
        bool couleur;
        Coordonnees coods;
    public:
        Piece();
        virtual ~Piece() = default;
        virtual std::vector<std::pair<int,int>> deplacements(Plateau g) = 0;
};

#endif