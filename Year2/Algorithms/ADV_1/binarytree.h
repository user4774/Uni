#ifndef TREE_BINARYTREE_H
#define TREE_BINARYTREE_H


#include <iostream>
#include <memory>
#include "node.h"


class BinaryTree {
public:
    std::shared_ptr<Node> root;

    BinaryTree();

    void insert(int data);

    bool remove(int target);

    int find_i(int target);

    int find_r(int target);

private:
    void insert(int data, const std::shared_ptr<Node> node);

    void leftRight(std::shared_ptr<Node> node);

    bool _find_r(int target, std::shared_ptr<Node> node);
};


#endif //TREE_BINARYTREE_H
