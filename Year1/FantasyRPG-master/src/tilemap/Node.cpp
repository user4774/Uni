
#include "Node.h"

Node::Node(int _locationX, int _locationY, int _targetX, int _targetY, std::shared_ptr<Node> previous_ptr)
: previous(std::move(previous_ptr)){
    locationX = _locationX;
    locationY = _locationY;
    targetX = _targetX;
    targetY = _targetY;

    if (previous == nullptr) {
        g = 0;
    } else if ((previous->locationX < locationX && previous->locationY < locationY)
               || (previous->locationX > locationX && previous->locationY > locationY)
               || ((previous->locationX < locationX && previous->locationY > locationY))
               || (previous->locationX > locationX && previous->locationY < locationY)){
        g = previous->g + 1.4;
    } else {
        g = previous->g + 1;
    }
}

bool operator==(const Node& node, const Node& other) {
    if (node.getX() == other.getX() && node.getY() == other.getY()) {
        return true;
    }
    return false;
}
