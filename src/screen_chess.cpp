#include "screen_chess.hpp"
#include "screen_main_menu.hpp"

ChessScreen::ChessScreen(GameController &game):Screen(game),side{false},finished{false}
{
    const std::string basePath = "assets/";

    this->addImage(AssetID::chessBoard,basePath+"board_b&g.png");

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

ChessScreen::~ChessScreen()
{
    for(auto it=images.begin();it != images.end();++it)
    {
        UnloadImage(it->second);
    }

    for(auto it=textures.begin();it != textures.end();++it)
    {
        UnloadTexture(it->second);
    }
}

AssetID ChessScreen::getAssetForPiece(const Piece& piece,bool color)
{
    int base=static_cast<int>(piece.getType())*2;
    int colorOffset=color ? 0 : 1;

    return static_cast<AssetID>(base+colorOffset);
}

void ChessScreen::drawAsset(AssetID id, int x, int y, int size)
{
    Texture2D& tex = textures.at(id);

    Rectangle source = {0, 0, (float)tex.width, (float)tex.height};
    Rectangle dest = {(float)x, (float)y, (float)size, (float)size};

    DrawTexturePro(tex, source, dest, {0, 0}, 0.0f, WHITE);
}

std::string ChessScreen::getCoords(int squareSize)
{
    int x=GetMouseX()/squareSize;
    int y=GetMouseY()/squareSize;

    x=x>0 ? x:0;
    x=x<8 ? x:7;

    y=y>0 ? y:0;
    y=y<8 ? y:7;

    if(side)
    {
       y=7-y;
       x=7-x;
    }

    char a='a'+x;
    char b='8'-y;
    std::string res="  ";
    res[0]=a;
    res[1]=b;

    return res;
}

void ChessScreen::drawPieces(int squareSize)
{
    for(int i = 0; i < 8 ; ++i)
    {
        for(int j = 0 ; j < 8 ; ++j)
        {
            Coordinates c;
            c.setXY(j,i);

            Piece *p;

            Player &p1=game.getJ1();
            Player &p2=game.getJ2();
            
            if(!side) p=p1.getPiece(c);
            else p=p2.getPiece(c);
            if(p!=nullptr){
                int x=side ? (7-j)*squareSize : j*squareSize;
                int y=side ? (7-i)*squareSize : i*squareSize;
                drawAsset(getAssetForPiece(*p,!side),x,y,squareSize);
            }
            
            if(!side) p=p2.getPiece(c);
            else p=p1.getPiece(c);
            if(p!=nullptr){
                int x=side ? (7-j)*squareSize : j*squareSize;
                int y=side ? (7-i)*squareSize : i*squareSize;
                drawAsset(getAssetForPiece(*p,side),x,y,squareSize);
            }
        }
    }
}

void ChessScreen::addImage(AssetID id,const std::string &path)
{
    Image img=LoadImage(path.c_str());
    Texture2D texture=LoadTextureFromImage(img);
    images[id]=img;
    textures[id]=texture;
}

void ChessScreen::switchSide()
{
    side=!side;
    std::cout<<"switchside side ="<<side<<std::endl;
    
}

void ChessScreen::update()
{
    if(IsKeyPressed(KEY_TAB))
    {
        finished=true;
    }
} 
void ChessScreen::draw()
{
    int width=GetScreenWidth();
    int height=GetScreenHeight();
    int boardSize = width < height ? width:height;
    int squareSize = boardSize/8;

    BeginDrawing();
    ClearBackground(BLACK);
    drawAsset(AssetID::chessBoard,0,0,boardSize);
    drawPieces(squareSize);

    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        std::cout<<getCoords(squareSize)<<"\n";
    }
        
    if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
    {
        switchSide();
    }   
    EndDrawing();
}

bool ChessScreen::isFinished()
{
    return finished;
}

std::unique_ptr<Screen> ChessScreen::nextScreen()
{
    return std::make_unique<MainMenuScreen>(game,1000,1000);
}