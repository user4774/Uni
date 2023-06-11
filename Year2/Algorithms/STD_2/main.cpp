#include <iostream>
#include "binarytree.h"

int main() {

    BinaryTree bst = BinaryTree();
    bst.insert(7);
    bst.insert(4);
    bst.insert(9);
    bst.insert(8);
    bst.insert(13);
    bst.insert(12);
    bst.insert(10);
    bst.insert(11);
    bst.remove(9);
    int answer = bst.find_i(7);
    int answerR = bst.find_r(7);
    int wrongAnswer = bst.find_i(12);
    int wrongAnswerR = bst.find_r(12);
    std::cout << answer << ' ' << answerR << ' ' << wrongAnswer << ' ' << wrongAnswerR << std::endl;
    return 0;
}
