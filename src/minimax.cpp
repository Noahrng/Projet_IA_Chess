#include "minimax.hpp"

/*----------------------Constructeurs / Destructeurs----------------------*/
Minimax::Minimax(GameController &game,Evaluator &eval):game{game},eval{eval},minimax_depth{4},quiescence_depth{4}
{
  
}

/*--------------------------------Getters---------------------------------*/
ChessMove Minimax::getBestMoveFork()
/*
    Description:
        Renvoie le meilleur mouvement Calculé
        Cette méthode réalise des fork , un pour chaque mouvement racine de départ , 
        et envoie ces resultat dans un tableau de tube , pour que le procesus parent les receptionne
*/
{
    signal(SIGCHLD,SIG_IGN);

    std::vector<std::pair<Coordinates,Coordinates>> rootMoves;

    Player& current = game.getCurrentPlayer();
    for(size_t i = 0;i<current.nbOfPieces();i++)
    {
        game.choosePiece(i);
        Coordinates from = game.getCoordsPieceChosen();
        Coordinates moves[218];
        int size_move=game.movesOfPieceChosen(moves);
        game.unChoosePiece();

        sortMovesWithPrevious(moves,size_move,from,previous_best);

        for(int j=0;j<size_move;j++)
        {
            std::shared_ptr<Piece> mover = current.getPiece(from);
            if(mover && mover->getValue() >= 5.0 && isLosingMove(from, moves[j])) continue;
            rootMoves.push_back({from,moves[j]});
        }
    }

    int N = (int)rootMoves.size();
    if(N==0) return ChessMove();

    std::vector<std::array<int,2>> pipes(N);
    for(int i=0;i<N;i++)
    {
        if(pipe(pipes[i].data())==-1)
        {
            std::cerr << "pipe() failed\n";
            exit(0);
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
                if(game.isRepeat())
                    score=0.0;
                else
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
                exit(0);
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
            exit(0);
        }
        close(pipes[i][0]);

        if(maximizing ? result.score > best.score : result.score < best.score)
        {
            best.score=result.score;
            best.from=Coordinates(result.fx,result.fy);
            best.to=Coordinates(result.tx,result.ty);
        }

        else if(result.score==best.score)
        {
            Coordinates to(result.tx, result.ty);
            if(game.pieceEnemyDetection(to) && !game.pieceEnemyDetection(best.to))
            {
                best.from = Coordinates(result.fx, result.fy);
                best.to   = to;
            }
        }
    }

    previous_best=best;
    return best;
}

int Minimax::getDepth()
/*
    Description:
        Renvoie le parametre de profondeur de minimax
*/
{
    return minimax_depth;
}

/*------------------------------Mise à Jour-------------------------------*/
void Minimax::add_minimax_depth()
/*
    Description:
        ajoute 2 au paramametre de profondeur de minimax
    Note:
        minimax_depth ne peut pas dépasser 6
*/
{
    minimax_depth=std::min(6,minimax_depth+2);
}

void Minimax::sub_minimax_depth()
/*
    Description:
        enleve 2 au paramametre de profondeur de minimax
    Note:
        minimax_depth ne peut être inferieur a 2
*/
{
    minimax_depth=std::max(2,minimax_depth-2);
}

/*--------------------------Vérification d'État---------------------------*/
bool Minimax::isLosingCapture(const Coordinates from, const Coordinates to)
/*
    Description:
        renvoie si le mouvement de from a to est une capture perdante
*/
{
    std::shared_ptr<Piece> attacker = game.getCurrentPlayer().getPiece(from);
    std::shared_ptr<Piece> victim   = game.getWaitingPlayer().getPiece(to);

    if(!attacker || !victim) return false;

    // Si on gagne autant ou plus qu'on perd → jamais perdant
    if(attacker->getValue() <= victim->getValue() + 2.0) return false;

    // Simuler la capture
    attacker->moveTo(to);
    victim->moveTo(Coordinates(-1,-1));  // retirer temporairement

    // Compter les défenseurs de la case après la capture
    bool defended = false;
    size_t nb = game.getWaitingPlayer().nbOfPieces();
    for(size_t k = 0; k < nb; k++)
    {
        std::shared_ptr<Piece> defender = game.getWaitingPlayer().getPiece(k);
        if(defender == victim) continue;
        if(!defender->getCoordinates().onBoard()) continue;
        if(defender->canEatPattern(to) &&
           !game.pieceInBetween(defender->getCoordinates(), to))
        {
            defended = true;
            break;
        }
    }

    // Annuler la simulation
    attacker->moveTo(from);
    victim->moveTo(to);

    if(defended)
        return true;  // capture perdante

    return false;
}

bool Minimax::isLosingMove(const Coordinates from,const Coordinates to)
/*
    Description:
        renvoie si le mouvement de from a to est un mouvement perdant
*/
{
    std::shared_ptr<Piece> mover  = game.getCurrentPlayer().getPiece(from);
    std::shared_ptr<Piece> victim = game.getWaitingPlayer().getPiece(to);

    if(!mover) return false;

    // Capture gagnante ou égale → jamais perdant
    if(victim && mover->getValue() <= victim->getValue() + 2.0) return false;

    double gain = victim ? victim->getValue() : 0.0;

    // Simuler le déplacement
    mover->moveTo(to);
    if(victim) victim->moveTo(Coordinates(-1,-1));

    // Vérifier si la case to est attaquée après le déplacement
    bool attacked = false;
    size_t nb = game.getWaitingPlayer().nbOfPieces();
    for(size_t k = 0; k < nb; k++)
    {
        std::shared_ptr<Piece> defender = game.getWaitingPlayer().getPiece(k);
        if(defender == victim) continue;
        if(!defender->getCoordinates().onBoard()) continue;
        if(defender->canEatPattern(to) &&
           !game.pieceInBetween(defender->getCoordinates(), to))
        {
            attacked = true;
            break;
        }
    }

    // Annuler la simulation
    mover->moveTo(from);
    if(victim) victim->moveTo(to);

    if(attacked && mover->getValue() > gain + 1.0)
        return true;  // on perd plus qu'on ne gagne

    return false;
}

/*----------------------------------Tris----------------------------------*/
void Minimax::sortMoves(Coordinates* moves, int size, const Coordinates from)
/*
    Description:
        trie moves en fonction de plusieurs comparaison
    Note:
        Les capture sont en premier
        sinon on prefere des capture la plus precieuse
        sinon on prefere les case les plus proche du centre
*/
{
    std::sort(moves, moves + size,
        [this, from](const Coordinates &a, const Coordinates &b)
        {
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

void Minimax::sortMovesWithPrevious(Coordinates *moves,int size,Coordinates from,const ChessMove &prev_best)
/*
    Description:
        Comme sortMoves excepté sauf que le meilleur mouvement précendant est placé en premier 
*/
{
    std::sort(moves, moves+size,
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
double Minimax::minimax(const int depth,const bool maximizing,double alpha,double beta)
/*
    Description:
        Applique l'algorithme Minimax avec élagage alpha-béta
*/
{
    if(game.isDraw()) return 0.0;

    if(depth<=0)
    {
        return quiescence(alpha,beta,maximizing,quiescence_depth);
    }


    double best=maximizing ? -100.0 : 100.0;
    bool has_move=false;
    Player &current=game.getCurrentPlayer();
    size_t nb_piece=current.nbOfPieces();
    Coordinates list_move[218];

    for(size_t i=0;i<nb_piece;i++)
    {
        game.choosePiece(i);
        Coordinates cell_choose=game.getCoordsPieceChosen();
        int size_move=game.movesOfPieceChosen(list_move);
        game.unChoosePiece();

        sortMoves(list_move,size_move,cell_choose);

        for(int j=0;j<size_move;j++)
        {
            std::shared_ptr<Piece> mover = game.getCurrentPlayer().getPiece(cell_choose);
            if(has_move && mover && mover->getValue() >= 3.0 && isLosingMove(cell_choose,list_move[j])) continue;
            if(game.movePiece(cell_choose,list_move[j],true))
            {
                has_move=true;
                game.switchTurn();
                if(maximizing)
                {
                    best=std::max(best,minimax(depth-1,!maximizing,alpha,beta));
                    game.unMove();
                    if(best>=beta)
                        return best;
                    alpha=std::max(alpha,best);
                }
                else
                {
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
        if(game.isChecked()) return maximizing ? -1.0 : 1.0;
        return 0.0;
    }

    return best;
}

double Minimax::quiescence(double alpha,double beta,const bool maximizing,int depth)
/*
    Description:
        Applique la quiescence a une profondeur limité
    Note:
        il est utile pour explorer quand on atteint depth=0 dans minimax de l'appeller pour explorer des coup supplémentaire qui
        sont des coups de capture
*/
{
    if(depth == 0)
        return eval.evaluate();

    double stand_pat = eval.evaluate(); // score de base

    if(maximizing)
    {
        if(stand_pat >= beta) return stand_pat;
        if(stand_pat > alpha) alpha = stand_pat;
    }
    else
    {
        if(stand_pat <= alpha) return stand_pat;
        if(stand_pat < beta)   beta = stand_pat;
    }

    Player &current = game.getCurrentPlayer();
    size_t nb_piece = current.nbOfPieces();

    Coordinates list_move[218];

    for(size_t i = 0; i < nb_piece; i++)
    {
        
    
        game.choosePiece(i);
        Coordinates cell_choose = game.getCoordsPieceChosen();
        int size_move=game.movesOfPieceChosen(list_move);
        game.unChoosePiece();

        for(int j = 0; j < size_move; j++)
        {
            if(!game.pieceEnemyDetection(list_move[j])) continue;
            if(isLosingCapture(cell_choose, list_move[j])) continue;

            if(game.movePiece(cell_choose, list_move[j], true))
            {
                game.switchTurn();
                double score = quiescence(alpha, beta, !maximizing, depth-1);
                game.unMove();

                if(maximizing)
                {
                    if(score >= beta)  return score;
                    if(score > alpha)  alpha = score;
                }
                else
                {
                    if(score <= alpha) return score;
                    if(score < beta)   beta = score;
                }
            }
        }
    }
    return maximizing ? alpha : beta;
}