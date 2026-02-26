#ifndef GAME_ASSET
#define GAME_ASSET

#include <raylib-5.5_linux_amd64/include/raylib.h>
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
        GameAsset(const std::string&,int,int,int);
        ~GameAsset();

        void setPosition(int,int);
        void setSize(int);
        void setTint(Color);
        void resetTint();

        void draw() override;
        bool isHovered(Vector2 mouse) override;
        float getCenterX() override;
        float getCenterY() override;
        float getWidth() override;
        float getHeight() override;
        void setBackgroundColor(Color) override;   


};

#endif