#ifndef PIECES_HPP
#define PIECES_HPP
#include <coordonnees.hpp>

class Piece  {
    private:
        bool couleur;
        Coordonnees coords;
    public:
        Piece(bool, Coordonnees);
        virtual ~Piece() = default;
        virtual bool se_deplacer(Coordonnees) = false;
};

#endif