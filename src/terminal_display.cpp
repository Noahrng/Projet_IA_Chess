#include "terminal_display.hpp"
#include <iostream>


TerminalDisplay::TerminalDisplay(GameController &game,Minimax &robot,bool s): Display(game,robot,s){

}

/*-----------------------------Entrées joueur-----------------------------*/
std::string TerminalDisplay::playerEntryString()
{
    std::string entry;
    std::cin>>entry;
    return entry;
} 

/*---------------------Test  sur   entrée  du  joueur---------------------*/
bool TerminalDisplay::isGameQuitted(std::string s)
{
    if(s == "quit") return true;
    return false;
}

bool TerminalDisplay::moveCancelled(std::string s)
{
    return (s == "cancel");
}

bool TerminalDisplay::isLetter(char c)
{
    return (c >= 'a' && c<='z') || (c >= 'A' && c<= 'Z');
}

bool TerminalDisplay::isNumber(char c)
{
    return (c >= '0' && c<='9');
}

/*---------------------------Conversions String---------------------------*/
Coordinates TerminalDisplay::convertStringIntoCoords(std::string move)
{
    int i= -1;
    int j= -1;
    if(move.length() == 2){
        if(isLetter(move[1]) && isNumber(move[0])){
            if(move[1] <= 'h'){
                j=move[1] - 'a';
            }
            if(move[0] >= '1' && move[0] <= '8'){
                i = 7- (move[0] - '1');
            }
        }
        else if (isLetter(move[0]) && isNumber(move[1]))
        {
            if(move[0] <= 'h'){
                j=move[0] - 'a';
            }
            if(move[1] >= '1' && move[1] <= '8'){
                i = 7-(move[1] - '1');
            }
        }
    }

    Coordinates c(j,i);

    return c;
}

PieceType TerminalDisplay::convertStringIntoType(std::string type)
{
    if(type == "queen") return PieceType::Queen;
    if(type == "bishop") return PieceType::Bishop;
    if(type == "knight") return PieceType::Knight;
    if(type == "rook") return PieceType::Rook;
    else return PieceType::Nothing; 
}

/*-------------------------Affichage  du terminal-------------------------*/
void TerminalDisplay::printBoard()
{
    bool color_turn = game.blackTurn();
    std::string colored_cell;
    std::string end_color = "\033[0m";

    std::string legal_moves = "\033[93m";

    if(!color_turn)
    {
        colored_cell = "\033[47;30m";
        std::cout<< colored_cell << "    White's Turn    ";
    } 
    else{
        colored_cell = "\033[40;37m"; 
        std::cout << colored_cell << "    Black's Turn    ";
    }
    
    std::cout << end_color << std::endl ;
    for(int i = 0; i < 8 ; ++i)
    {
        if(side)   std::cout << colored_cell << " " << i+1 << end_color;
        else        std::cout << colored_cell << " " << 9-(i+1) << end_color;

        for(int j = 0 ; j < 8 ; ++j)
        {
            Coordinates c;
            if(!side)   c.setXY(j,i);
            else        c.setXY(7-j,7-i);

            std::shared_ptr<Piece> p;
            if((i+j)%2==0){
                std::cout << "\033[48;2;245;222;179m";
            }
            else{
                std::cout << "\033[48;2;34;139;34m";
            }

            Player &p1=game.getCurrentPlayer();
            Player &p2=game.getWaitingPlayer();

            if( (p=p1.getPiece(c)) != nullptr){
                if(!color_turn){
                    std::cout << "\033[97m" << p->getTerminalSprite() << " " << end_color;
                }
                else{
                    std::cout << "\033[30m" << p->getTerminalSprite() << " " << end_color;
                }
            }
            else if((p=p2.getPiece(c)) != nullptr){
                if(color_turn){
                    std::cout << "\033[97m" << p->getTerminalSprite() << " " << end_color;
                }
                else{
                    std::cout << "\033[30m" << p->getTerminalSprite() << " " << end_color;
                }
            }
            else if(game.isChosen()){
                Coordinates coords_piece_chosen = game.getCoordsPieceChosen();
                if(game.isEmpty(c))
                {
                    if(game.isLegalMove(coords_piece_chosen,c))
                    {
                        std::cout << legal_moves << "◯ " << end_color;
                    }
                    else
                    {
                        std::cout << "  ";
                    }
                }
                else
                {
                    std::cout << "  ";
                }
                
            }
            else{
                std::cout << "  ";
            }

            std::cout << "\033[0m";
        }
        std::cout << colored_cell << "  " << end_color <<  "\n";
    }
    std::cout << colored_cell << "  ";
    for(int j = 0 ; j < 8 ; ++j)
    {
        char letter;
        if(side)
        {
            letter = 'h' - j;
        }
        else
        {
            letter = 'a' + j;
        }
        std::cout << letter << " ";
    }
    std::cout << "  " << end_color << "\n";
}

void TerminalDisplay::clearTerminal()
{
    std::cout << "\x1B[2J\x1B[H";
}

void TerminalDisplay::printInfosPromote()
{
    std::cout << "Promotion : queen, rook, bishop, knight" << "\n";
}

/*----------------------------Exécution du jeu----------------------------*/
void TerminalDisplay::run()
{
    bool quit = false;
    bool checkmate = false;
    while(1 && !quit && !checkmate)
    {
        std::string string_coords;
        Coordinates c;
        //Couleurs ANSI
        std::string error_color = "\033[41;37m"; //Fond Rouge, Texte Blanc
        std::string end_color = "\033[0m"; //Fin Couleur
        
        bool coords_onboard;
        bool got_moved = false;
        bool cancel_move;
        bool piece_belong_to;
        
        checkmate = game.isCheckmate();
        

        while(!got_moved && !quit && !checkmate){
            clearTerminal();
            printBoard();
            coords_onboard = false;
            cancel_move = false;
            piece_belong_to = false;

            while((!coords_onboard || !piece_belong_to) && !quit)
            {
                std::cout << "Entrez les coordonnées d'une de vos pièces :\n";
                string_coords = playerEntryString();
                if(isGameQuitted(string_coords)) quit = true;
                else
                {
                    c=convertStringIntoCoords(string_coords);
                    if(c.onBoard())
                    {
                        coords_onboard = true;
                        game.choosePiece(c);
                        if(!game.isNull())
                        {
                            piece_belong_to = true;
                        }
                        else
                        {
                            std::cout << error_color <<
                            "/!\\ Coordonnées invalides, il n'y a pas de pièce qui vous appartient.\n"
                            << end_color;
                        }
                    }
                    else
                    {
                        std::cout << error_color <<
                        "/!\\ Coordonnées invalides, elles ne sont pas sur le plateau !\n"
                        << end_color;

                    }
                }
            }

            clearTerminal();
            printBoard();

            while(!got_moved && !cancel_move && !quit)
            {
                std::cout << "Entrez les coordonnées pour déplacer votre pièce (cancel si vous voulez annulez votre coup) :\n";
                string_coords = playerEntryString();
                if(isGameQuitted(string_coords)) quit = true;
                else if(moveCancelled(string_coords)) cancel_move = true;
                else
                {
                    c=convertStringIntoCoords(string_coords);
                    got_moved = game.movePiece(game.getCoordsPieceChosen(),c);
                    if(!c.onBoard() || !got_moved) 
                        std::cout << error_color << 
                        "/!\\ Coordonnées invalides, vous ne pouvez pas bouger ici !\n"
                        << end_color;
                }
            }
            if(got_moved && game.promotionPending())
            {
                std::string promotion;
                PieceType t = PieceType::Nothing;

                while(t == PieceType::Nothing)
                {
                    clearTerminal();
                    printBoard();
                    printInfosPromote();
                    std::cout << "Quelle pièce choisissez-vous pour la promotion ?\n";
                    
                    promotion = playerEntryString();
                    t = convertStringIntoType(promotion);
                }
                //Promouvoir la pièce
                Player& curr = game.getCurrentPlayer();
                std::shared_ptr<Piece> p = curr.getPiece(c);
                game.promoteTo(p,t);
            }
            game.unChoosePiece();
        }
        if(!checkmate) game.switchTurn();
    }

}