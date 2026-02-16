#include <graphic_display.hpp>
GraphicDisplay::GraphicDisplay(int w,int h,const std::string &t,Player &j1, Player &j2,bool s):
    Display(j1,j2,s),
    width{w},
    height{h},
    title{t}
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(width,height,title.c_str());
    SetTargetFPS(30);
    this->addImage(AssetID::chessBoard,"assets/board_b&g.png");

    const std::string basePath = "assets/";

    this->addImage(AssetID::pawnWhite,basePath+"w_Pawn.png");
    this->addImage(AssetID::pawnBlack,basePath+"b_Pawn.png");

    this->addImage(AssetID::bishopWhite,basePath+"w_Bishop.png");
    this->addImage(AssetID::bishopBlack,basePath+"b_Bishop.png");

    this->addImage(AssetID::kingWhite,basePath+"w_King.png");
    this->addImage(AssetID::kingBlack,basePath+"b_King.png");

    this->addImage(AssetID::knightWhite,basePath+"w_Knight.png");
    this->addImage(AssetID::knightBlack,basePath+"b_Knight.png");

    this->addImage(AssetID::queenWhite,basePath+"w_Queen.png");
    this->addImage(AssetID::queenBlack,basePath+"b_Queen.png");

    this->addImage(AssetID::rookWhite,basePath+"w_Rook.png");
    this->addImage(AssetID::rookBlack,basePath+"b_Rook.png");


}

GraphicDisplay::~GraphicDisplay(){
    //auto ici est std::map<std::string,T>::iterator
    for(auto it=images.begin();it != images.end();++it)
    {
        UnloadImage(it->second);
    }

    for(auto it=textures.begin();it != textures.end();++it)
    {
        UnloadTexture(it->second);
    }
    CloseWindow();
}

void GraphicDisplay::addImage(AssetID id,const std::string &path)
{
    Image img=LoadImage(path.c_str());
    Texture2D texture=LoadTextureFromImage(img);
    images[id]=img;
    textures[id]=texture;
}


void GraphicDisplay::drawAsset(AssetID id, int x, int y, int size)
{
    Texture2D& tex = textures.at(id);

    Rectangle source = {0, 0, (float)tex.width, (float)tex.height};
    Rectangle dest = {(float)x, (float)y, (float)size, (float)size};

    DrawTexturePro(tex, source, dest, {0, 0}, 0.0f, WHITE);
}

std::string GraphicDisplay::getCoords(int squareSize)
{
    int x=GetMouseX()/squareSize;
    int y=GetMouseY()/squareSize;

    char a='a'+x;
    char b='8'-y;
    std::string res="  ";
    res[0]=a;
    res[1]=b;

    std::cout<<res<<"\n";

    return res;
}

void GraphicDisplay::updateDimensions()
{
    width=GetScreenWidth();
    height=GetScreenHeight();
}

AssetID GraphicDisplay::getAssetForPiece(const Piece& piece,bool color)
{
    int base=static_cast<int>(piece.getType())*2;
    int colorOffset=color ? 1 : 0;

    return static_cast<AssetID>(base+colorOffset);
}

void GraphicDisplay::drawPieces(int squareSize)
{
    for(int i = 0; i < 8 ; ++i)
    {
        for(int j = 0 ; j < 8 ; ++j)
        {
            Coordinates c(j,i);
            Piece *p=p1.getPiece(c);
            if(p!=nullptr){
                int x=c.getX()*squareSize;
                int y=c.getY()*squareSize;
                drawAsset(getAssetForPiece(*p,false),x,y,squareSize);
            }
            
            p=p2.getPiece(c);
            if(p!=nullptr){
                int x=c.getX()*squareSize;
                int y=c.getY()*squareSize;
                drawAsset(getAssetForPiece(*p,true),x,y,squareSize);
            }
        }
    }
}

void GraphicDisplay::run()
{
    while(!WindowShouldClose())
    {
        if(IsWindowResized())
        {
            updateDimensions();
        }

        

        int boardSize = width < height ? width:height;
        int squareSize = boardSize/8;

        BeginDrawing();
        ClearBackground(WHITE);
        drawAsset(AssetID::chessBoard,0,0,boardSize);
        drawPieces(squareSize);

        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            std::cout<<getCoords(squareSize)<<"\n";
        }

        

        EndDrawing();
    }
}