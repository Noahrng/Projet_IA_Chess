#include "game_asset.hpp"

GameAsset::GameAsset(const std::string &path,int x,int y,int size)
    :x{x},y{y},size{size},tint{WHITE}
{
    image=LoadImage(path.c_str());
    texture=LoadTextureFromImage(image);
}

GameAsset::~GameAsset()
{
    UnloadImage(image);
    UnloadTexture(texture);
}

void GameAsset::setPosition(int newX,int newY)
{
    x=newX;
    y=newY;
}

void GameAsset::setSize(int newSize)
{
    size=newSize;
}

void GameAsset::setTint(Color color)
{
    tint=color;
}

void GameAsset::resetTint(){
    tint=WHITE;
}

bool GameAsset::isHovered(Vector2 mouse)
{
    return CheckCollisionPointRec(mouse,{(float)x,(float)y,(float)size,(float)size});
}

float GameAsset::getCenterX()
{
    return x+size/2.0f;
}

float GameAsset::getCenterY()
{
    return y+size/2.0f;
}

float GameAsset::getWidth()
{
    return (float)size;
}

float GameAsset::getHeight()
{
    return (float)size;
}

void GameAsset::setBackgroundColor(Color c)
{
    setTint(c);
}

void GameAsset::draw()
{
    Rectangle source ={0,0,(float)texture.width,(float)texture.height};
    Rectangle dest={(float)x,(float)y,(float)size,(float)size};
    DrawTexturePro(texture,source,dest,{0,0},0.0f,tint);
}
