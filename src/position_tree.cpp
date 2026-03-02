#include "position_tree.hpp"
#include "evaluator.hpp"

PositionTree::PositionTree(GameController &g):game{g}
{
    root=std::make_shared<Position>(Coordinates(-1,-1),Coordinates(-1,-1),0.0);
}

std::vector<Coordinates> PositionTree::generateMovesForPieces(Piece* p)
{
    std::vector<Coordinates> moves;
    Coordinates from = p->getCoordinates();

    switch(p->getType())
    {
        // Pièces à déplacement limité : on teste seulement les cases atteignables
        case PieceType::Knight:
        {
            int deltas[8][2] = {{1,2},{2,1},{-1,2},{-2,1},{1,-2},{2,-1},{-1,-2},{-2,-1}};
            for(int d = 0; d < 8; d++)
            {
                Coordinates to(from.getX()+deltas[d][0], from.getY()+deltas[d][1]);
                if(to.onBoard() && game.isLegalMoveFast(from, to))
                    moves.push_back(to);
            }
            break;
        }
        case PieceType::King:
        {
            for(int dx = -1; dx <= 1; dx++)
            for(int dy = -1; dy <= 1; dy++)
            {
                if(dx==0 && dy==0) continue;
                Coordinates to(from.getX()+dx, from.getY()+dy);
                if(to.onBoard() && game.isLegalMoveFast(from, to))
                    moves.push_back(to);
            }
            break;
        }
        case PieceType::Pawn:
        {
            int dir = game.getCurrentPlayer().isWhite() ? -1 : 1;
            // Avance
            Coordinates to1(from.getX(), from.getY()+dir);
            Coordinates to2(from.getX(), from.getY()+2*dir);
            Coordinates eat1(from.getX()-1, from.getY()+dir);
            Coordinates eat2(from.getX()+1, from.getY()+dir);
            if(to1.onBoard()  && game.isLegalMoveFast(from, to1))  moves.push_back(to1);
            if(to2.onBoard()  && game.isLegalMoveFast(from, to2))  moves.push_back(to2);
            if(eat1.onBoard() && game.isLegalMoveFast(from, eat1)) moves.push_back(eat1);
            if(eat2.onBoard() && game.isLegalMoveFast(from, eat2)) moves.push_back(eat2);
            break;
        }
            
        case PieceType::Rook:
        {
            // 4 directions : haut, bas, gauche, droite
            int directions[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};
            scanRays(from, directions, 4, moves);
            break;
        }
        case PieceType::Bishop:
        {
            // 4 diagonales
            int directions[4][2] = {{1,1},{1,-1},{-1,1},{-1,-1}};
            scanRays(from, directions, 4, moves);
            break;
        }
        case PieceType::Queen:
        {
            // 8 directions
            int directions[8][2] = {{0,1},{0,-1},{1,0},{-1,0},{1,1},{1,-1},{-1,1},{-1,-1}};
            scanRays(from, directions, 8, moves);
            break;
        }
    }
    return moves;
}

void PositionTree::scanRays(Coordinates from, int directions[][2], int nb_dirs, std::vector<Coordinates>& moves)
{
    for(int d = 0; d < nb_dirs; d++)
    {
        int dx = directions[d][0];
        int dy = directions[d][1];

        int x = from.getX() + dx;
        int y = from.getY() + dy;

        while(x >= 0 && x < 8 && y >= 0 && y < 8)
        {
            Coordinates to(x, y);

            if(game.pieceAllyDetection(to))
            {
                break;  // pièce alliée : on s'arrête, case non jouable
            }
            else if(game.pieceEnemyDetection(to))
            {
                // pièce ennemie : on peut manger mais on s'arrête après
                if(game.isLegalMoveFast(from, to))
                    moves.push_back(to);
                break;
            }
            else
            {
                // case vide : coup possible
                if(game.isLegalMoveFast(from, to))
                    moves.push_back(to);
            }

            x += dx;
            y += dy;
        }
    }
}

std::shared_ptr<Position> PositionTree::getRoot()
{
    return root;
}

void PositionTree::build(int depth)
{
    minimax(root,2*depth,true,-2.0,2.0);
}

double PositionTree::minimax(std::shared_ptr<Position> node,int depth,bool maximizing,double alpha,double beta) 
{
    Evaluator eval(game);
    node->eval_score=eval.evaluate();
    if(depth==0)
    {   
        node->score = node->eval_score;
        return node->score;
    }

    std::vector<std::pair<Coordinates,Coordinates>> legal_moves;
    Player& current=game.getCurrentPlayer();
    std::size_t nb=current.nbOfPieces();

    for(std::size_t i = 0;i < nb;i++)
    {
        Piece *p = current.getPiece(i).get();
        std::vector<Coordinates> pieces_moves = generateMovesForPieces(p);
        Coordinates from = p->getCoordinates();
        for(std::size_t j=0;j<pieces_moves.size();j++)
        {
            legal_moves.push_back(std::pair<Coordinates,Coordinates>(from,pieces_moves[j]));
        }
    }

    if(legal_moves.empty())
    {
        node->score = maximizing ? -1.0 : 1.0;
        return node->score;
    }

    double best = maximizing ? -2.0:2.0;

    for(std::size_t m=0;m<legal_moves.size();m++)
    {
        Coordinates from = legal_moves[m].first;
        Coordinates to = legal_moves[m].second;

        std::shared_ptr<Position> child = std::make_shared<Position>(from,to,0.0);
        child->parent=node;
        node->children.push_back(child);

        bool moved=game.movePiece(from,to);
        if(!moved) continue;

        game.switchTurn();

        double score=minimax(child,depth-1,!maximizing,alpha,beta);

        game.unMove();

        if(maximizing)
        {   
            if(score>best) best=score;
            if(best>alpha) alpha = best;
        }
        else
        {
            if(score<best) best = score;
            if(best<beta) beta = best;
        }

        if(beta <= alpha) break;
    }

    node->score = best;
    return best;
}

std::shared_ptr<Position> PositionTree::bestMove()
{
    if(root->children.empty()) return nullptr;

    std::shared_ptr<Position> best = root->children[0];

    for(size_t i = 1; i < root->children.size(); i++)
    {
        if(root->children[i]->score > best->score)
            best = root->children[i];
    }
    return best;
}

void PositionTree::print(std::shared_ptr<Position> node, int depth)
{
    for(int i = 0; i < depth; i++) std::cout << "  ";
    std::cout << "coup: (" << node->from.getX() << "," << node->from.getY() << ")"
              << " -> (" << node->to.getX() << "," << node->to.getY() << ")"
              << " score: " << node->score << "\n";

    for(size_t i = 0; i < node->children.size(); i++)
        print(node->children[i], depth + 1);
}

void PositionTree::printToFile(std::shared_ptr<Position> node, int depth, std::ofstream& file)
{
    for(int i = 0; i < depth; i++) file << "  ";

    std::string player    = (depth % 2 == 1) ? "[Blanc]" : "[Noir]";
    std::string advantage;
    if(node->score > 0.1)       advantage = "avantage blanc";
    else if(node->score < -0.1) advantage = "avantage noir";
    else if(node->score >=1.0) advantage = "mat blanc";
    else if(node->score <=-1.0) advantage = "mat noir";
    else                        advantage = "egal";

    file << player
         << " (" << node->from.getX() << "," << node->from.getY() << ")"
         << " -> "
         << " (" << node->to.getX()   << "," << node->to.getY()   << ")"
         << " eval: "    << node->eval_score
         << " minimax: " << node->score
         << " " << advantage
         << "\n";

    for(size_t i = 0; i < node->children.size(); i++)
        printToFile(node->children[i], depth + 1, file);
}

void PositionTree::printToFile(const std::string& path)
{
    std::ofstream file(path);
    if(!file.is_open())
    {
        std::cerr << "Erreur : impossible d'ouvrir " << path << "\n";
        return;
    }
    printToFile(root, 0, file);
    file.close();
}