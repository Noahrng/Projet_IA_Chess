#ifndef TREE_HPP
#define TREE_HPP

#include <memory>
#include <vector>
#include <functional>

template<typename T>
struct Node
{
    T data;
    std::weak_ptr<Node<T>> parent;
    std::vector<std::shared_ptr<Node<T>>> enfants;

    Node(T data) : data{data} {}
};

template<typename T>
class Tree
{
    protected:
        std::shared_ptr<Node<T>> root;
    
    public:
        Tree() : root{nullptr} {}
        Tree(T rootData) : root{std::make_shared<Node<T>>(rootData)} {}
        Tree(T rootData,int size_enfants) : root{std::make_shared<Node<T>>(rootData)}
        {
            root->enfants.reserve(size_enfants);
        }

        std::shared_ptr<Node<T>> getRoot() {return root;}

        void addChild(std::shared_ptr<Node<T>> parent,T data)
        {
            std::shared_ptr<Node<T>> enfant = std::make_shared<Node<T>>(data);
            enfant->parent = parent;
            parent->enfants.push_back(enfant);
        }

        void addChild(std::shared_ptr<Node<T>> parent,T data,int size_enfants)
        {
            std::shared_ptr<Node<T>> enfant = std::make_shared<Node<T>>(data);
            enfant->enfants.reserve(size_enfants);
            enfant->parent = parent;
            parent->enfants.push_back(enfant);
        }

        bool isLeaf(std::shared_ptr<Node<T>> node)
        {
            return node->enfants.empty();
        }

        bool isRoot(std::shared_ptr<Node<T>> node)
        {
            return node->parent.expired();
        }

        void dfs(std::shared_ptr<Node<T>> node,std::function<void(std::shared_ptr<Node<T>>)> fn)
        {
            if(!node) return;
            fn(node);
            for(auto& enfant : node->enfants)
                dfs(enfant,fn);
        }

        size_t size(std::shared_ptr<Node<T>> node)
        {
            if(!node) return 0;
            size_t total = 1;
            for(auto& enfant : node->enfants)
                total+=size(enfant);
            return total;
        }
};


#endif