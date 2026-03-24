#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <raylib.h>
#include <memory>
#include "game_controller.hpp"
#include "minimax.hpp"

class Screen
{
    protected:
        GameController& game;
        Minimax& robot;
            
    public:
        //Constructeurs / Destructeurs
        Screen(GameController&,Minimax&);
        virtual ~Screen()=default;

        //Vérification d'État
        virtual bool isFinished()=0;
        
        //Mise à Jour
        virtual void update()=0;
        virtual std::unique_ptr<Screen> nextScreen()=0;

        //Dessiner l'Écran
        virtual void draw()=0;
};

#endif