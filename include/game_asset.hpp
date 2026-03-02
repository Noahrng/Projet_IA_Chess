#ifndef GAME_ASSET
#define GAME_ASSET

#include <raylib-5.5_linux_amd64/include/raylib.h>
#include <string>

class GameAsset
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
        void draw();


};

#endif