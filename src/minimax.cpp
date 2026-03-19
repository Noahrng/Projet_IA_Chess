#include "minimax.hpp"

Minimax::Minimax(GameController &game,Evaluator &eval):game{game},eval{eval},nb_node{0}
{
    start_time=std::chrono::high_resolution_clock::now();
}

double Minimax::minimax(int depth,bool maximizing,double alpha,double beta)
{
    nb_node++;

    if(nb_node%10000==0)
    {
        auto now = std::chrono::high_resolution_clock::now();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now - start_time).count();

        if(ms>0)
        {
            std::cout<<"nb_node="<<nb_node<<std::endl;
            size_t nodes_per_sec=nb_node * 1000/ms;
            std::cout << "nb_node=" << nb_node 
                      << " | " << nodes_per_sec << " noeuds/s"
                      << " | " << ms << " ms"
                      << std::endl;
        }
        
    }
    if(depth==0)
    {
        double score=eval.evaluate();
        return score;
    }
    

    double best;

    if(maximizing)
    {
        best=-100.0;
        Player &current=game.getCurrentPlayer();
        size_t nb_piece=current.nbOfPieces();
        for(size_t i=0;i<nb_piece;i++)
        {
            std::vector<Coordinates> list_move;
            list_move.reserve(28);
            game.choosePiece(i);
            Coordinates cell_choose=game.getCoordsPieceChosen();
            game.movesOfPieceChosen(list_move);
            game.unChoosePiece();
            size_t size_move=list_move.size();
            for(size_t j=0;j<size_move;j++)
            {
                if(game.movePiece(cell_choose,list_move[j],true))
                {
                    game.switchTurn();
                    best=std::max(best,minimax(depth-1,!maximizing,alpha,beta));
                    game.unMove();
                    if(best>=beta)
                        return best;
                    alpha=std::max(alpha,best);
                }
            }
        }
    }
    else
    {
        best=100.0;
        Player &current=game.getCurrentPlayer();
        size_t nb_piece=current.nbOfPieces();
        for(size_t i=0;i<nb_piece;i++)
        {
            std::vector<Coordinates> list_move;
            list_move.reserve(28);
            game.choosePiece(i);
            Coordinates cell_choose=game.getCoordsPieceChosen();
            game.movesOfPieceChosen(list_move);
            game.unChoosePiece();
            size_t size_move=list_move.size();
            for(size_t j=0;j<size_move;j++)
            {
                if(game.movePiece(cell_choose,list_move[j],true))
                {
                    game.switchTurn();
                    best=std::min(best,minimax(depth-1,!maximizing,alpha,beta));
                    game.unMove();
                    if(alpha>=best)
                        return best;
                    beta=std::min(beta,best);
                }
            }
        }

    }
    return best;
}

ChessMove Minimax::getBestMove()
{
    nb_node=0;
    start_time=std::chrono::high_resolution_clock::now();

    ChessMove best;
    bool maximizing=game.whiteTurn();
    best.score = maximizing ? -100.0 : 100.0;

    double alpha = 2.0;
    double beta = 2.0;

    Player &current = game.getCurrentPlayer();
    size_t nb_piece = current.nbOfPieces();

    std::vector<Coordinates> list_move;
    list_move.reserve(28);

    for(size_t i=0;i<nb_piece;i++)
    {
        std::cout<<"i="<<i<<std::endl;
        game.choosePiece(i);
        Coordinates cell_choose=game.getCoordsPieceChosen();
        game.movesOfPieceChosen(list_move);
        game.unChoosePiece();

        size_t size_move=list_move.size();
        for(size_t j=0;j<size_move;j++)
        {
            if(game.movePiece(cell_choose,list_move[j],true))
            {
                game.switchTurn();
                double score = minimax(7,!maximizing,alpha,beta);
                game.unMove();

                if(maximizing && score > best.score)
                {
                    best.score=score;
                    best.from=cell_choose;
                    best.to=list_move[j];
                    alpha=std::max(alpha,best.score);
                }
                else if(!maximizing && score < best.score)
                {
                    best.score=score;
                    best.from=cell_choose;
                    best.to=list_move[j];
                    beta=std::min(beta,best.score);
                }
            }
        }
    }

    std::cout << "Meilleur coup : " << best.from << " -> " << best.to
              << " score=" << best.score << std::endl;

    return best;
}