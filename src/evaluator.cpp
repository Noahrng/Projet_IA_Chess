#include "evaluator.hpp"

/*----------------------Constructeurs / Destructeurs----------------------*/
Evaluator::Evaluator(GameController &game):game{game}, MAX_MATERIAL{39.0},MAX_POSITION{8.0}
{

}

/*--------------------------------Getters---------------------------------*/
double Evaluator::getPieceTableValue(Piece &p, bool isWhite) const
{
    int x = p.getCoordinates().getX();
    int y = p.getCoordinates().getY();

    // Les noirs voient le tableau à l'envers
    int row = isWhite ? y : (7 - y);

    switch(p.getType())
    {
        case PieceType::Pawn:   return PAWN_TABLE[row][x];
        case PieceType::Knight: return KNIGHT_TABLE[row][x];
        case PieceType::Bishop: return BISHOP_TABLE[row][x];
        case PieceType::Rook:   return ROOK_TABLE[row][x];
        case PieceType::Queen:  return QUEEN_TABLE[row][x];
        case PieceType::King:   
            return isEndGame() ? KING_ENDGAME_TABLE[row][x] : KING_TABLE[row][x];
        default: return 0.0;
    }
}

/*-----------------------------Verification-------------------------------*/
bool Evaluator::isEndGame() const
{
    Player &current = game.getCurrentPlayer();
    Player &waiting = game.getWaitingPlayer();

    size_t n1 = current.nbOfPieces();
    size_t n2 = waiting.nbOfPieces();

    std::shared_ptr<Piece> queen_current=current.getPiece(1);
    std::shared_ptr<Piece> queen_waiting=waiting.getPiece(1);

    bool no_queen=queen_current->getType()!=PieceType::Queen && queen_current->getType()!=PieceType::Queen;

    bool onlyPawn=true;
    for(size_t i=0;i<n1;i++)
    {
        if(current.getPiece(i)->getType()!=PieceType::Pawn) onlyPawn=false;
    }

    for(size_t i=0;i<n2;i++)
    {
        if(waiting.getPiece(i)->getType()!=PieceType::Pawn) onlyPawn=false;
    }
    return (no_queen && n1+n2<=8) || onlyPawn;
}

/*------------------------------Évaluations-------------------------------*/
double Evaluator::evaluateMaterial() const
{
    double white_score=0.0;
    double black_score=0.0;
    Player &current = game.getCurrentPlayer();
    Player &waiting = game.getWaitingPlayer();
    Player &white = current.isWhite() ? current : waiting;
    Player &black = current.isBlack() ? current : waiting;

    for(size_t i = 1; i < white.nbOfPieces();i++)
    {
        std::shared_ptr<Piece> p = white.getPiece(i);
        white_score+=p->getValue();
    }
    for(size_t i = 1; i < black.nbOfPieces();i++)
    {
        std::shared_ptr<Piece> p = black.getPiece(i);
        black_score+=p->getValue();
    }
    return white_score-black_score;
}



double Evaluator::evaluatePosition() const
{   
    double white_score = 0.0;
    double black_score = 0.0;

    Player &current = game.getCurrentPlayer();
    Player &waiting = game.getWaitingPlayer();
    Player &white   = current.isWhite() ? current : waiting;
    Player &black   = current.isBlack() ? current : waiting;

    std::vector<std::shared_ptr<Piece>>& w_piece=white.getPieces();
    std::vector<std::shared_ptr<Piece>>& b_piece=black.getPieces();

    size_t w_nb_piece=w_piece.size();
    size_t b_nb_piece=b_piece.size();

    for(size_t i = 0; i < w_nb_piece; i++)
    {
        white_score += getPieceTableValue(*(w_piece[i]), true);
    }
    for(size_t i = 0; i < b_nb_piece; i++)
    {
        black_score += getPieceTableValue(*(b_piece[i]), false);
    }
    return white_score - black_score;
}

double Evaluator::evaluateKingPositionSingle(Player &player,bool isWhite) const
{
    double penalty = 0.0;

    std::shared_ptr<Piece> king;
    std::vector<std::shared_ptr<Piece>> rooks;

    auto &pieces = player.getPieces();

    for(auto &p : pieces)
    {
        if(!p->getCoordinates().onBoard()) continue;

        if(p->getType() == PieceType::King)
            king = p;
        else if(p->getType() == PieceType::Rook)
            rooks.push_back(p);
    }

    if(!king) return 0.0;

    int kx = king->getCoordinates().getX();
    int ky = king->getCoordinates().getY();

    for(auto &rook : rooks)
    {
        int rx = rook->getCoordinates().getX();
        int ry = rook->getCoordinates().getY();

        // même colonne
        if(rx == kx)
        {
            // roi devant la tour = bloque
            if((isWhite && ky > ry) || (!isWhite && ky < ry))
            {
                penalty -= 0.3;
            }
        }
    }

    return penalty;
}

double Evaluator::evaluateKingPosition() const
{
    double score = 0.0;

    Player &current = game.getCurrentPlayer();
    Player &waiting = game.getWaitingPlayer();

    Player &white = current.isWhite() ? current : waiting;
    Player &black = current.isBlack() ? current : waiting;

    score += evaluateKingPositionSingle(white, true);
    score -= evaluateKingPositionSingle(black, false);

    return score;
}
double Evaluator::evaluate() const
{
    double material = evaluateMaterial()/MAX_MATERIAL;
    double position = evaluatePosition()/MAX_POSITION;
    double penalty=evaluateKingPosition();


    double pos_weight = isEndGame() ?  0.2 : 0.1;
    double mat_weight = 1.0-pos_weight;

    double score = mat_weight*material+(pos_weight+penalty)*position;

    return std::clamp(score,-0.99,0.99);
}

