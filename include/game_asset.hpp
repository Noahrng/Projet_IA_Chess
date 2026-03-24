#ifndef GAME_ASSET
#define GAME_ASSET

#include <raylib.h>
#include <string>
#include "drawable.hpp"

class GameAsset : public Drawable
{
    private:
        Image image;
        Texture2D texture;
        int x,y,size;
        Color tint;
    public:
        //Constructeurs / Destructeurs
        GameAsset(const std::string&,int,int,int);
        ~GameAsset();

        //Getters
        float getCenterX() override;
        float getCenterY() override;
        float getWidth() override;
        float getHeight() override;

        //Setters
        void setPosition(int,int);
        void setSize(int);
        void setTint(Color);
        void resetTint();
        void setBackgroundColor(Color) override;   

        //Vérification d'État
        bool isHovered(Vector2 mouse) override;

        //Dessiner Asset
        void draw() override;


};

#endif