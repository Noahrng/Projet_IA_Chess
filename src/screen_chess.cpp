#include "screen_chess.hpp"
#include "screen_main_menu.hpp"
#include "evaluator.hpp"

/*----------------------Constructeurs / Destructeurs----------------------*/
ChessScreen::ChessScreen(GameController &game,Minimax &robot):Screen(game,robot),side{false},finished{false},promoted{Coordinates(-1,-1)},color{false}
{
    const std::string basePath = "assets/";
    srand(0);

    this->addImage(AssetID::chessBoard,basePath+"Board1.png");

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

/*--------------------------------Getters---------------------------------*/
AssetID ChessScreen::getAssetForPiece(const Piece& piece,bool color)
/*
    Description:
        Renvoie en fonction de la couleur et du type de la pièce correspondant
        l'id de l'asset
*/
{
    int base=static_cast<int>(piece.getType())*2;
    int colorOffset=color ? 0 : 1;

    return static_cast<AssetID>(base+colorOffset);
}

AssetID ChessScreen::getAssetForPiece(const PieceType& piece,bool color)
/*
    Description:
        Renvoie en fonction de la couleur et du type de la pièce correspondant
        l'id de l'asset
*/
{
    int base=static_cast<int>(piece)*2;
    int colorOffset=color ? 0 : 1;

    return static_cast<AssetID>(base+colorOffset);
}

Coordinates ChessScreen::getCoords(int squareSize)
/*
    Description:
        Renvoie une coordonnée en fonction de la position courante de la souris
    Note:
        L'abscisse et l'ordonné sont compris entre 0 et 7 inclu
*/
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

/*--------------------------Vérification d'État---------------------------*/
bool ChessScreen::isFinished()
/*
    Description:
        Renvoie si l'écran courant est terminé
*/
{
    return finished;
}

/*------------------------------Mise à Jour-------------------------------*/
void ChessScreen::update()
/*
    Description:
        Actualise les paramètre en fonction d'input utilisateur
*/
{
    if(IsKeyPressed(KEY_TAB))
    {
        finished=true;
    }
} 

std::unique_ptr<Screen> ChessScreen::nextScreen()
/*
    Description:
        Renvoie la prochaine instance de screen après le screen courant
*/
{
    return std::make_unique<MainMenuScreen>(game,robot,1000,1000);
}

/*----------------------------Action du Joueur----------------------------*/
void ChessScreen::scrollPiece(Coordinates c,int squareSize)
/*
    Description:
        Quand une promotion est attendue, on demande au joueur en quelle pièce
        il veut promouvoir le pion, ce choix, ce fait au scroll de la souris
*/
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

void ChessScreen::switchSide()
/*
    Description:
        Inverse side
    Note:
        à pour effet de retourner le plateau d'echec
*/
{
    side=!side;
}

/*--------------------------------Texture---------------------------------*/
void ChessScreen::addImage(AssetID id,const std::string &path)
/*
    Description:
        Ajoute une image dans images , en fonction de path
    Note:
        Chaque images possede une clé id de type AssetID
*/
{
    images[id]=std::make_unique<GameAsset>(path,0,0,0);
}

/*----------------------------Dessiner le Jeu-----------------------------*/
void ChessScreen::drawAsset(AssetID id, int x, int y, int size,Color tint)
/*
    Description:
        Affiche l'asset en fonction de id , avec des paramètres de position , de taille , et de teinte
*/
{
    images.at(id)->setPosition(x,y);
    images.at(id)->setSize(size);
    images.at(id)->setTint(tint);
    images.at(id)->draw();
    images.at(id)->resetTint();
}

void ChessScreen::drawPieces(int squareSize,Coordinates choose)
/*
    Description:
        Affiche l'ensemble des pièces
    Note:
        La piece choisi a une teinte jaune
        Le roi si il est en échec est affiché avec une teinte jaune
*/
{
    Player &p1=game.getCurrentPlayer();
    Player &p2=game.getWaitingPlayer();
    auto lastMove=game.getLastMove();
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
                if(p->getCoordinates()==lastMove.second)
                {
        
                    DrawRectangle(side ? (7-lastMove.first.getX())*squareSize+3 : lastMove.first.getX()*squareSize+3,
                                  side ? (7-lastMove.first.getY())*squareSize+3 : lastMove.first.getY()*squareSize+3,
                                  squareSize,squareSize,
                                  {255,255,0,80});

                    DrawRectangle(side ? (7-lastMove.second.getX())*squareSize+3 : lastMove.second.getX()*squareSize+3,
                                  side ? (7-lastMove.second.getY())*squareSize+3 : lastMove.second.getY()*squareSize+3,
                                  squareSize,squareSize,
                                  {255,255,0,80});
                }
                drawAsset(id,x,y,squareSize,c == choose ? YELLOW : WHITE);
            }

        }
    }
}

void ChessScreen::drawCircles(int squareSize,std::vector<Coordinates> coords)
/*
    Description:
        Affiche des cercles sur les cases en fonction d'un vecteur de coordonnées
    Note:
        Utilisé pour afficher les coups légaux de la pièce choisie
*/
{
    for(std::size_t i=0;i<coords.size();i++)
    {
        int x=side ? 7-coords[i].getX() : coords[i].getX();
        int y=side ? 7-coords[i].getY() : coords[i].getY();
        DrawCircle(squareSize*x+squareSize/2,squareSize*y+squareSize/2,squareSize/4,Color{0,0,0,75});

    }
}

void ChessScreen::draw()
/*
    Description:
        Affichage
*/
{
    int width=GetScreenWidth();
    int height=GetScreenHeight();
    int boardSize = width < height ? width:height;
    int squareSize = boardSize/8;

    bool checkmate = game.isCheckmate();
    bool draw = !checkmate && game.isDraw();

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
    
    if((IsKeyPressed(KEY_BACKSPACE) || IsKeyPressedRepeat(KEY_BACKSPACE)) && !game.promotionPending())
    {
        std::cout<<"Annulation\n";
        game.unMove();
        game.unMove();
    }

    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !checkmate && !draw)
    {
        Coordinates c=getCoords(squareSize);

        if(!game.isChosen())
        {
            game.choosePiece(c);
        }
        else
        {
            Coordinates from=game.getCoordsPieceChosen();
            if(game.movePiece(from,c))
            {
                promoted = c;
                color=game.getCurrentPlayer().isWhite();
                if(!game.promotionPending()) game.switchTurn();
            }
            
            game.unChoosePiece();

            
            
            
        }        
        
    }
        
    if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
    {
        switchSide();
    }   

    
    
    if(checkmate)
    {
        DrawText("ECHEC",10,height/8,200,RED);
        DrawText("ET",10,height/8+200,200,RED);
        DrawText("MAT",10,height/8+400,200,RED);

        DrawText("Echap pour quitter",10,height/8 +600,50,BLACK);
    }

    else if(draw)
    {
        DrawText("ÉGALITÉ",10,height/8+200,200,RED);

        DrawText("Echap pour quitter",10,height/8 +600,50,BLACK);
    }

    else
    {
        if(game.getCurrentPlayer().isBot())
        {
            ChessMove bestm=robot.getBestMoveFork();
            if(game.movePiece(bestm.from,bestm.to,true)) game.switchTurn();
        }
    }
    

    char data_depth[12];
    std::sprintf(data_depth,"Depth=%d",(robot.getDepth()));
    DrawText(data_depth,10,10,50,YELLOW);

    if(IsKeyPressed(KEY_LEFT))
    {
        robot.sub_minimax_depth();
    }

    if(IsKeyPressed(KEY_RIGHT))
    {
        robot.add_minimax_depth();
    }



    EndDrawing();

    

}
