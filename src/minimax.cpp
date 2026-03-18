#include "minimax.hpp"

Minimax::Minimax(GameController &game,Evaluator &eval):game{game},eval{eval},nb_node{0}
{
    start_time=std::chrono::high_resolution_clock::now();
}

double Minimax::minimax(int depth,bool maximizing,double alpha,double beta)
{
    nb_node++;

    if(nb_node%1000==0)
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
                //if(game.movePiece(cell_choose,list_move[j]))
                //{
                    game.switchTurn();
                    best=std::max(best,minimax(depth-1,!maximizing,alpha,beta));
                    if(best>=beta)
                        return best;
                    alpha=std::max(alpha,best);
                    game.unMove();
                //}
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
                //if(game.movePiece(cell_choose,list_move[j]))
                //{
                    game.switchTurn();
                    best=std::min(best,minimax(depth-1,!maximizing,alpha,beta));
                    if(alpha>=best)
                        return best;
                    beta=std::min(beta,best);
                    game.unMove();
                //}
            }
        }

    }
    return best;


}