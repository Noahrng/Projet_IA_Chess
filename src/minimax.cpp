#include "minimax.hpp"

/*----------------------Constructeurs / Destructeurs----------------------*/
Minimax::Minimax(GameController &game,Evaluator &eval):game{game},eval{eval}
{
  
}

/*--------------------------------Getters---------------------------------*/
ChessMove Minimax::getBestMoveFork()
{
    update_depth();

    std::vector<std::pair<Coordinates,Coordinates>> rootMoves;

    Player& current = game.getCurrentPlayer();
    for(size_t i = 0;i<current.nbOfPieces();i++)
    {
        game.choosePiece(i);
        Coordinates from = game.getCoordsPieceChosen();
        std::vector<Coordinates> moves;
        game.movesOfPieceChosen(moves);
        game.unChoosePiece();

        for(auto& to : moves)
        {
            rootMoves.push_back({from,to});
        }
    }

    int N = (int)rootMoves.size();

    std::vector<std::array<int,2>> pipes(N);
    for(int i=0;i<N;i++)
    {
        if(pipe(pipes[i].data())==-1)
        {
            std::cerr << "pipe() failed\n";
            exit(1);
        }
    }

    bool maximizing = game.whiteTurn();

    for(int i = 0;i<N;i++)
    {
        pid_t pid=fork();
        if(pid==0)
        {
            for(int j=0;j<N;j++)
            {
                if(j!=i){
                    close(pipes[j][0]);
                    close(pipes[j][1]);
                }
            }
            close(pipes[i][0]);

            auto [from,to] = rootMoves[i];
            double score = -100.0;

            if(game.movePiece(from,to,true)){
                game.switchTurn();
                score=minimax(minimax_depth-1,!maximizing,-2.0,2.0);
                game.unMove();
            }

            struct {double score; int fx,fy,tx,ty;} result;
            result.score=score;
            result.fx=from.getX();
            result.fy=from.getY();
            result.tx=to.getX();
            result.ty=to.getY();

            if(write(pipes[i][1],&result,sizeof(result))==-1)
            {
                std::cerr << "write() failed\n";
                exit(1);
            }
            close(pipes[i][1]);
            exit(0);
        }
        else{
            close(pipes[i][1]);
        }
    }

    ChessMove best;
    best.score=maximizing ? -100.0 : 100.0;

    for(int i=0;i<N;i++)
    {
        struct { double score; int fx,fy,tx,ty; } result;
        if(read(pipes[i][0],&result,sizeof(result))==-1)
        {
            std::cerr << "read() failed\n";
            exit(1);
        }
        close(pipes[i][0]);

        if(maximizing ? result.score > best.score : result.score < best.score)
        {
            best.score=result.score;
            best.from=Coordinates(result.fx,result.fy);
            best.to=Coordinates(result.tx,result.ty);
        }
    }

    for(int i=0;i<N;i++)
    {
        wait(nullptr);
    }

    return best;
}

ChessMove Minimax::getBestMoveAtDepth(int depth, double alpha, double beta)
{
    std::cout << "debut getBestMoveAtDepth depth=" << depth << std::endl;
    std::cout << "blanc=" << game.whiteTurn() << std::endl;
    ChessMove best;
    bool maximizing = game.whiteTurn();
    best.score = maximizing ? -100.0 : 100.0;

    Player &current = game.getCurrentPlayer();
    size_t nb_piece = current.nbOfPieces();

    std::vector<Coordinates> list_move;
    list_move.reserve(28);

    for(size_t i = 0; i < nb_piece; i++)
    {
        game.choosePiece(i);
        Coordinates cell_choose = game.getCoordsPieceChosen();
        game.movesOfPieceChosen(list_move);
        game.unChoosePiece();

        // Tri avec le meilleur coup de la profondeur précédente
        sortMovesWithPrevious(list_move, cell_choose, previous_best);

        size_t size_move = list_move.size();

        for(size_t j = 0; j < size_move; j++)
        {
            if(isLosingCapture(cell_choose,list_move[j])) continue;
            if(game.movePiece(cell_choose, list_move[j], true))
            {
                game.switchTurn();
                double score;
                if(game.isRepeat())
                    score=0.0;
                else 
                    score=minimax(depth - 1, !maximizing, alpha, beta);
                game.unMove();

                if(maximizing)
                {
                    if(score > best.score)
                    {
                        best.score = score;
                        best.from  = cell_choose;
                        best.to    = list_move[j];
                        alpha      = std::max(alpha, best.score);

                        if(best.score >= 1.0) return best;
                    }
                    else if(score == best.score)
                    {
                        if(game.pieceEnemyDetection(list_move[j]) &&
                           !game.pieceEnemyDetection(best.to))
                        {
                            best.from = cell_choose;
                            best.to   = list_move[j];
                        }
                    }
                }
                else
                {
                    if(score < best.score)
                    {
                        best.score = score;
                        best.from  = cell_choose;
                        best.to    = list_move[j];
                        beta       = std::min(beta, best.score);

                        if(best.score <= -1.0) return best;
                    }
                    else if(score == best.score)
                    {
                        if(game.pieceEnemyDetection(list_move[j]) &&
                           !game.pieceEnemyDetection(best.to))
                        {
                            best.from = cell_choose;
                            best.to   = list_move[j];
                        }
                    }
                }
            }
        }
    }
    return best;
}

ChessMove Minimax::getBestMove()
{
    update_depth();
    // Réinitialiser le meilleur coup précédent
    previous_best = ChessMove();

    ChessMove best;

    for(int d = 1; d <= minimax_depth; d++)
    {
        double alpha = -2.0;
        double beta  =  2.0;

        ChessMove result = getBestMoveAtDepth(d, alpha, beta);

        // Mettre à jour le meilleur coup pour trier à la prochaine profondeur
        previous_best = result;
        best = result;

        if(best.score>=1.0 || best.score <=-1.0)
        {
            std::cout << "Mat trouvé a depth=" << d << std::endl;
            break;
        }
    }
    return best;
}


/*------------------------------Mise à Jour-------------------------------*/
void Minimax::update_depth()
{
    size_t nbpiece=game.getCurrentPlayer().nbOfPieces()+game.getWaitingPlayer().nbOfPieces();
    if(game.getCurrentPlayer().nbOfPieces()==1 || game.getWaitingPlayer().nbOfPieces() == 1)
    {
        minimax_depth=8;
    }
    else if(nbpiece < 12)
    {
        minimax_depth=6;
    }
    else
    {
        minimax_depth=4;
        quiescence_depth=2;
    }
}

/*--------------------------Vérification d'État---------------------------*/
bool Minimax::isLosingCapture(Coordinates from, Coordinates to)
{
    std::shared_ptr<Piece> attacker = game.getCurrentPlayer().getPiece(from);
    std::shared_ptr<Piece> victim   = game.getWaitingPlayer().getPiece(to);

    if(!attacker || !victim) return false;
    if(attacker->getValue() <= victim->getValue() + 2.0) return false;

    // Vérifier si la case est défendue par une pièce adverse
    size_t nb = game.getWaitingPlayer().nbOfPieces();
    for(size_t k = 0; k < nb; k++)
    {
        std::shared_ptr<Piece> defender = game.getWaitingPlayer().getPiece(k);
        if(defender == victim) continue;
        if(defender->canEatPattern(to) &&
           !game.pieceInBetween(defender->getCoordinates(), to))
        {
            return true; // capture perdante
        }
    }
    return false;
}

/*----------------------------------Tris----------------------------------*/
void Minimax::sortMoves(std::vector<Coordinates> &moves, Coordinates from)
{
    std::sort(moves.begin(), moves.end(),
        [this, from](Coordinates &a,Coordinates &b)
        {
            // Priorité 1 : captures MVV-LVA
            bool a_capture = game.pieceEnemyDetection(a);
            bool b_capture = game.pieceEnemyDetection(b);

            if(a_capture != b_capture) return a_capture > b_capture;

            if(a_capture && b_capture)
            {
                // Les deux sont des captures → préférer capturer la pièce la plus précieuse
                std::shared_ptr<Piece> victim_a = game.getWaitingPlayer().getPiece(a);
                std::shared_ptr<Piece> victim_b = game.getWaitingPlayer().getPiece(b);
                return victim_a->getValue() > victim_b->getValue();
            }

            // Priorité 2 : proximité au centre
            int a_dist = a.distX(3) + a.distY(3);
            int b_dist = b.distX(3) + b.distY(3);
            return a_dist < b_dist;
        }
    );
}

void Minimax::sortMovesWithPrevious(std::vector<Coordinates> &moves,
                                     Coordinates from,
                                     const ChessMove &prev_best)
{
    std::sort(moves.begin(), moves.end(),
        [this, from, &prev_best](Coordinates &a, Coordinates &b)
        {
            bool a_is_best = (from == prev_best.from && a == prev_best.to);
            bool b_is_best = (from == prev_best.from && b == prev_best.to);
            if(a_is_best != b_is_best) return a_is_best > b_is_best;

            bool a_capture = game.pieceEnemyDetection(a);
            bool b_capture = game.pieceEnemyDetection(b);
            if(a_capture != b_capture) return a_capture > b_capture;

            if(a_capture && b_capture)
            {
                std::shared_ptr<Piece> victim_a = game.getWaitingPlayer().getPiece(a);
                std::shared_ptr<Piece> victim_b = game.getWaitingPlayer().getPiece(b);
                return victim_a->getValue() > victim_b->getValue();
            }

            int a_dist = a.distX(3) + a.distY(3);
            int b_dist = b.distX(3) + b.distY(3);
            return a_dist < b_dist;
        }
    );
}

/*------------------------------Algorithmes-------------------------------*/
double Minimax::minimax(int depth,bool maximizing,double alpha,double beta)
{
    if(game.isRepeat()) return 0.0;

    if(depth==0)
    {
        return quiescence(alpha,beta,maximizing,quiescence_depth);
    }
    

    double best;
    bool has_move=false;

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

            sortMoves(list_move,cell_choose);

            size_t size_move=list_move.size();
            for(size_t j=0;j<size_move;j++)
            {
                if(isLosingCapture(cell_choose,list_move[j])) continue;
                if(game.movePiece(cell_choose,list_move[j],true))
                {
                    has_move=true;
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

            sortMoves(list_move,cell_choose);
            size_t size_move=list_move.size();
            for(size_t j=0;j<size_move;j++)
            {
                if(isLosingCapture(cell_choose,list_move[j])) continue;
                if(game.movePiece(cell_choose,list_move[j],true))
                {
                    has_move=true;
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

    if(!has_move)
    {
        if(game.isChecked())
            return maximizing ? -1.0 : 1.0;
        else
            return 0.0;
    }
    return best;
}

double Minimax::quiescence(double alpha, double beta, bool maximizing,int depth)
{
    if(depth == 0)
        return eval.evaluate();

    double stand_pat = eval.evaluate(); // score de base

    if(maximizing)
    {
        if(stand_pat >= beta) return stand_pat;
        if(stand_pat > alpha) alpha = stand_pat;

        Player &current = game.getCurrentPlayer();
        size_t nb_piece = current.nbOfPieces();

        for(size_t i = 0; i < nb_piece; i++)
        {
            std::vector<Coordinates> list_move;
            list_move.reserve(28);

            game.choosePiece(i);
            Coordinates cell_choose = game.getCoordsPieceChosen();
            game.movesOfPieceChosen(list_move);
            game.unChoosePiece();

            for(size_t j = 0; j < list_move.size(); j++)
            {
                // Seulement les captures !
                if(!game.pieceEnemyDetection(list_move[j])) continue;
                if(isLosingCapture(cell_choose,list_move[j])) continue;

                if(game.movePiece(cell_choose, list_move[j], true))
                {
                    game.switchTurn();
                    double score = quiescence(alpha, beta, !maximizing,depth-1);
                    game.unMove();

                    if(score >= beta)  return score;
                    if(score > alpha)  alpha = score;
                }
            }
        }
        return alpha;
    }
    else
    {
        if(stand_pat <= alpha) return stand_pat;
        if(stand_pat < beta)   beta = stand_pat;

        Player &current = game.getCurrentPlayer();
        size_t nb_piece = current.nbOfPieces();

        for(size_t i = 0; i < nb_piece; i++)
        {
            std::vector<Coordinates> list_move;
            list_move.reserve(28);

            game.choosePiece(i);
            Coordinates cell_choose = game.getCoordsPieceChosen();
            game.movesOfPieceChosen(list_move);
            game.unChoosePiece();

            for(size_t j = 0; j < list_move.size(); j++)
            {
                // Seulement les captures !
                if(!game.pieceEnemyDetection(list_move[j])) continue;
                if(isLosingCapture(cell_choose,list_move[j])) continue;

                if(game.movePiece(cell_choose, list_move[j], true))
                {
                    game.switchTurn();
                    double score = quiescence(alpha, beta, !maximizing,depth-1);
                    game.unMove();

                    if(score <= alpha) return score;
                    if(score < beta)   beta = score;
                }
            }
        }
        return beta;
    }
}