#ifndef TREE_NODE_H
#define TREE_NODE_H


#include <memory>

class Node {
public:
    int data;
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;

    explicit Node(const int *data=nullptr);
};


#endif //TREE_NODE_H
