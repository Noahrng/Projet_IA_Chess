#include "screen_chess.hpp"
#include "screen_main_menu.hpp"
#include "evaluator.hpp"

ChessScreen::ChessScreen(GameController &game,Minimax &robot):Screen(game,robot),side{false},finished{false},promoted{Coordinates(-1,-1)},color{false}
{
    const std::string basePath = "assets/";
    srand(0);

    this->addImage(AssetID::chessBoard,basePath+"Board.png");

    this->addImage(AssetID::pawnWhite,basePath+"WhitePawn.png");
    this->addImage(AssetID::pawnBlack,basePath+"BlackPawn.png");

    this->addImage(AssetID::bishopWhite,basePath+"WhiteBishop.png");
    this->addImage(AssetID::bishopBlack,basePath+"BlackBishop.png");

    this->addImage(AssetID::kingWhite,basePath+"WhiteKing.png");
    this->addImage(AssetID::kingBlack,basePath+"BlackKing.png");

    this->addImage(AssetID::knightWhite,basePath+"WhiteKnight.png");
    this->addImage(AssetID::knightBlack,basePath+"BlackKnight.png");

    this->addImage(AssetID::queenWhite,basePath+"WhiteQueen.png");
    this->addImage(AssetID::queenBlack,basePath+"BlackQueen.png");

    this->addImage(AssetID::rookWhite,basePath+"WhiteRook.png");
    this->addImage(AssetID::rookBlack,basePath+"BlackRook.png");
}

ChessScreen::~ChessScreen()
{
    
}

void ChessScreen::scrollPiece(Coordinates c,int squareSize)
{
    std::shared_ptr<Piece> p = game.getCurrentPlayer().getPiece(c);

    PieceType t[4]={PieceType::Rook,PieceType::Knight,PieceType::Bishop,PieceType::Queen};
    static int idx=0;
    
    if(GetMouseWheelMove()!=0.0)
    {
        idx=(idx+1)%4;
    }

    AssetID id=getAssetForPiece(t[idx],color);

    static unsigned char r=0,g=0,b=0;

    r=std::clamp((r+5)%255,150,256);
    g=std::clamp((g+5)%255,150,256);
    b=std::clamp((b+5)%255,150,256);

    Color couleur={r,g,b,255};

    drawAsset(id,0,0,8*squareSize,couleur);

    DrawText("Promotion",0,0,170,couleur);

    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        game.promoteTo(p,t[idx]);
        game.switchTurn();
    }
    


}

AssetID ChessScreen::getAssetForPiece(const Piece& piece,bool color)
{
    int base=static_cast<int>(piece.getType())*2;
    int colorOffset=color ? 0 : 1;

    return static_cast<AssetID>(base+colorOffset);
}

AssetID ChessScreen::getAssetForPiece(const PieceType& piece,bool color)
{
    int base=static_cast<int>(piece)*2;
    int colorOffset=color ? 0 : 1;

    return static_cast<AssetID>(base+colorOffset);
}

void ChessScreen::drawAsset(AssetID id, int x, int y, int size,Color tint)
{
    images.at(id)->setPosition(x,y);
    images.at(id)->setSize(size);
    images.at(id)->setTint(tint);
    images.at(id)->draw();
    images.at(id)->resetTint();
}

Coordinates ChessScreen::getCoords(int squareSize)
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

    return Coordinates{x,y};
}

void ChessScreen::drawPieces(int squareSize,Coordinates choose)
{
    Player &p1=game.getCurrentPlayer();
    Player &p2=game.getWaitingPlayer();
    for(int i = 0; i < 8 ; ++i)
    {
        for(int j = 0 ; j < 8 ; ++j)
        {
            Coordinates c;
            c.setXY(j,i);

            int x=side ? (7-j)*squareSize : j*squareSize;
            int y=side ? (7-i)*squareSize : i*squareSize;

            std::shared_ptr<Piece> p;

            p=p1.getPiece(c);
            if(p!=nullptr)
            {
                bool isWhite=p1.isWhite();
                AssetID id=getAssetForPiece(*p,isWhite);
                if(p->getType()==PieceType::King)
                {
                    if(game.isChecked())
                    {
                        drawAsset(id,x,y,squareSize,c == choose ? YELLOW : RED);
                    }
                    else
                        drawAsset(id,x,y,squareSize,c == choose ? YELLOW : WHITE);
                }
                else
                {
                    drawAsset(id,x,y,squareSize,c == choose ? YELLOW : WHITE);
                }
            }

            p=p2.getPiece(c);
            if(p!=nullptr)
            {
                bool isWhite=p2.isWhite();
                AssetID id=getAssetForPiece(*p,isWhite);
                drawAsset(id,x,y,squareSize,c == choose ? YELLOW : WHITE);
            }

        }
    }
}

void ChessScreen::drawCircles(int squareSize,std::vector<Coordinates> coords)
{
    for(std::size_t i=0;i<coords.size();i++)
    {
        int x=side ? 7-coords[i].getX() : coords[i].getX();
        int y=side ? 7-coords[i].getY() : coords[i].getY();
        DrawCircle(squareSize*x+squareSize/2,squareSize*y+squareSize/2,squareSize/4,Color{0,0,0,75});

    }
}

void ChessScreen::addImage(AssetID id,const std::string &path)
{
    images[id]=std::make_unique<GameAsset>(path,0,0,0);
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

    Evaluator eval(game);
    //std::cout<<"evaluation joueur: "<<eval.evaluate()<<std::endl;

    BeginDrawing();
    ClearBackground(BLACK);
    drawAsset(AssetID::chessBoard,0,0,boardSize);

    if(game.isChosen())
    {
        drawPieces(squareSize,game.getCoordsPieceChosen());
        drawCircles(squareSize,game.movesOfPieceChosen());
    }
    else
    {
        drawPieces(squareSize);
    }

    if(game.promotionPending())
    {
        scrollPiece(promoted,squareSize);
    }
    /*
    std::vector<Coordinates> c;
    c.push_back(Coordinates{4,4});
    c.push_back(Coordinates{5,5});
    c.push_back(Coordinates{6,6});
    drawCircles(squareSize,c);
    */
    
    if((IsKeyPressed(KEY_BACKSPACE) || IsKeyPressedRepeat(KEY_BACKSPACE)) && !game.promotionPending())
    {
        std::cout<<"Annulation\n";
        game.unMove();
    }

    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !game.isCheckmate())
    {
        Coordinates c=getCoords(squareSize);


        std::cout<<c<<"\n";

        if(!game.isChosen())
        {
            game.choosePiece(c);
        }
        else
        {
            Coordinates from=game.getCoordsPieceChosen();
            if(game.movePiece(from,c))
            {
                color=game.getCurrentPlayer().isWhite();
                if(!game.promotionPending()) game.switchTurn();
                //this->switchSide();
            }
            
            game.unChoosePiece();

            promoted=c;
            
            
            
        }        
        
    }
        
    if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
    {
        switchSide();
    }   

    
    
    if(game.isCheckmate())
    {
        DrawText("ECHEC",10,height/8,200,RED);
        DrawText("ET",10,height/8+200,200,RED);
        DrawText("MAT",10,height/8+400,200,RED);

        DrawText("Echap pour quitter",10,height/8 +600,50,BLACK);
    }
    
    EndDrawing();

    if(game.whiteTurn()){
        ChessMove bestm=robot.getBestMove();
        if(game.movePiece(bestm.from,bestm.to)) game.switchTurn();

    }
}

bool ChessScreen::isFinished()
{
    return finished;
}

std::unique_ptr<Screen> ChessScreen::nextScreen()
{
    return std::make_unique<MainMenuScreen>(game,robot,1000,1000);
}