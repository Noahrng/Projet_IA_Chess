#include "evaluator.hpp"

Evaluator::Evaluator(GameController &game):game{game}, MAX_MATERIAL{39.0},MAX_MOBILITY{50.0}
{

}

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

double Evaluator::evaluateMobility()
{
    double white_score=0.0;
    double black_score=0.0;
    Player &current = game.getCurrentPlayer();
    Player &waiting = game.getWaitingPlayer();

    Player &white = current.isWhite() ? current : waiting;
    Player &black = current.isBlack() ? current : waiting;

    for(size_t i=0;i<current.nbOfPieces();i++)
    {
        if(current.isWhite())
        {
            white_score+=game.CountMovesOfPiece(current.getPiece(i));
        }
        else
        {
            black_score+=game.CountMovesOfPiece(current.getPiece(i));
        }
    }

    game.switchTurn();

    for(size_t i=0;i<waiting.nbOfPieces();i++)
    {
        if(waiting.isWhite())
        {
            white_score+=game.CountMovesOfPiece(waiting.getPiece(i));
        }
        else
        {
            black_score+=game.CountMovesOfPiece(waiting.getPiece(i));
        }
    }
    game.switchTurn();

    std::cout << "white mobility: " << white_score << "\n";
    std::cout << "black mobility: " << black_score << "\n";

    return white_score-black_score;

}

double Evaluator::evaluate()
{
    if(game.isCheckmate())
    {
        return game.whiteTurn() ? -1.0 : 1.0;
    }

    double material = evaluateMaterial()/MAX_MATERIAL;
    double mobility = evaluateMobility()/MAX_MOBILITY;

    double score = 0.85*material+0.15*mobility;

    return std::clamp(score,-0.99,0.99);
}

