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
    this->addImage(AssetID::chessBoard,"assets/PixelArtChess/chess_pink/board.png");

    this->addImage(AssetID::pawnWhite,"assets/ChessAssets/w_Pawn.png");
    this->addImage(AssetID::pawnBlack,"assets/ChessAssets/b_Pawn.png");

    this->addImage(AssetID::bishopWhite,"assets/ChessAssets/w_Bishop.png");
    this->addImage(AssetID::bishopBlack,"assets/ChessAssets/b_Bishop.png");

    this->addImage(AssetID::kingWhite,"assets/ChessAssets/w_King.png");
    this->addImage(AssetID::kingBlack,"assets/ChessAssets/b_King.png");

    this->addImage(AssetID::knightWhite,"assets/ChessAssets/w_Knight.png");
    this->addImage(AssetID::knightBlack,"assets/ChessAssets/b_Knight.png");

    this->addImage(AssetID::queenWhite,"assets/ChessAssets/w_Queen.png");
    this->addImage(AssetID::queenBlack,"assets/ChessAssets/b_Queen.png");

    this->addImage(AssetID::rookWhite,"assets/ChessAssets/w_Rook.png");
    this->addImage(AssetID::rookBlack,"assets/ChessAssets/b_Rook.png");


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

        

        EndDrawing();
    }
}