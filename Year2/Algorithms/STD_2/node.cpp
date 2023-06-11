#include "node.h"

Node::Node(const int *value) {
    data = *value;
    left = nullptr;
    right = nullptr;
}
