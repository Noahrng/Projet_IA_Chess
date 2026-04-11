#include "game_asset.hpp"

/*----------------------Constructeurs / Destructeurs----------------------*/
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

/*--------------------------------Getters---------------------------------*/
float GameAsset::getCenterX()
/*
    Description:
        Retourne le centre X de l'asset courant
*/
{
    return x+size/2.0f;
}

float GameAsset::getCenterY()
/*
    Description:
        Retourne le centre Y de l'asset courant
*/
{
    return y+size/2.0f;
}

float GameAsset::getWidth()
/*
    Description:
        Retourne la largeur de l'asset
*/
{
    return (float)size;
}

float GameAsset::getHeight()
/*
    Description:
        Retourne la hauteur de l'asset
*/
{
    return (float)size;
}

/*--------------------------------Setters---------------------------------*/
void GameAsset::setPosition(int newX,int newY)
/*
    Description:
        Deplace l'asset vers une nouvelle position
*/
{
    x=newX;
    y=newY;
}

void GameAsset::setSize(int newSize)
/*
    Description:
        Change la taille de l'asset
*/
{
    size=newSize;
}

void GameAsset::setTint(Color color)
/*
    Description:
        Change le tint de l'asset
*/
{
    tint=color;
}

void GameAsset::resetTint()
/*
    Description:
        reset le tint de l'asset en blanc
*/
{
    tint=WHITE;
}

void GameAsset::setBackgroundColor(Color c)
/*
    Description:
        Change l'arriere plan (le tint) de l'asset
*/
{
    setTint(c);
}

bool GameAsset::isHovered(Vector2 mouse)
/*
    Description:
        renvoie si l'asset est survolé avec la souris
*/
{
    return CheckCollisionPointRec(mouse,{(float)x,(float)y,(float)size,(float)size});
}

/*----------------------------Dessiner Asset------------------------------*/
void GameAsset::draw()
/*
    Description:
        Affiche l'asset
*/
{
    Rectangle source ={0,0,(float)texture.width,(float)texture.height};
    Rectangle dest={(float)x,(float)y,(float)size,(float)size};
    DrawTexturePro(texture,source,dest,{0,0},0.0f,tint);
}
