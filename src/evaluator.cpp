#include "evaluator.hpp"

/*----------------------Constructeurs / Destructeurs----------------------*/
Evaluator::Evaluator(GameController &game):game{game}, MAX_MATERIAL{39.0},MAX_MOBILITY{50.0},MAX_POSITION{8.0}
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

    return n1+n2 <= 8;

    std::shared_ptr<Piece> queen_current=current.getPiece(1);
    std::shared_ptr<Piece> queen_waiting=waiting.getPiece(1);

    bool no_queen=queen_current->getType()!=PieceType::Queen && queen_current->getType()!=PieceType::Queen;

    return no_queen;
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

double Evaluator::evaluate() const
{
    double material = evaluateMaterial()/MAX_MATERIAL;
    double position = evaluatePosition()/MAX_POSITION;

    double pos_weight = isEndGame() ?  0.2 : 0.05;
    double mat_weight = 1.0-pos_weight;

    double score = mat_weight*material+pos_weight*position;

    return std::clamp(score,-0.99,0.99);
}

