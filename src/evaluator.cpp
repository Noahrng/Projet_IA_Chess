#include "evaluator.hpp"

/*----------------------Constructeurs / Destructeurs----------------------*/
Evaluator::Evaluator(GameController &game):game{game}, MAX_MATERIAL{39.0},MAX_MOBILITY{50.0},MAX_POSITION{8.0}
{

}

/*--------------------------------Getters---------------------------------*/
double Evaluator::getPieceTableValue(Piece &p, bool isWhite)
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
        case PieceType::King:   return KING_TABLE[row][x];
        default: return 0.0;
    }
}


/*------------------------------Évaluations-------------------------------*/
double Evaluator::evaluateMaterial()
{
    double white_score=0.0;
    double black_score=0.0;
    Player &current = game.getCurrentPlayer();
    Player &waiting = game.getWaitingPlayer();
    Player &white = current.isWhite() ? current : waiting;
    Player &black = current.isBlack() ? current : waiting;

    for(size_t i = 0; i < white.nbOfPieces();i++)
    {
        std::shared_ptr<Piece> p = white.getPiece(i);
        if(p!=nullptr && p->getType()!=PieceType::King)
        {
            white_score+=p->getValue();
        }
    }
    for(size_t i = 0; i < black.nbOfPieces();i++)
    {
        std::shared_ptr<Piece> p = black.getPiece(i);
        if(p!=nullptr && p->getType()!=PieceType::King)
        {
            black_score+=p->getValue();
        }
    }

    return white_score-black_score;
}



double Evaluator::evaluatePosition()
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

double Evaluator::evaluate()
{
    double material = evaluateMaterial()/MAX_MATERIAL;
    double position = evaluatePosition()/MAX_POSITION;
    double score = 0.85*material+0.15*position;

    return std::clamp(score,-0.99,0.99);
}

