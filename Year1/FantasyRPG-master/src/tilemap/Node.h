#ifndef FANTASYRPG_NODE_H
#define FANTASYRPG_NODE_H

#include <memory>

class Node {
private:
    std::shared_ptr<Node> previous;
    int locationX;
    int locationY;
    int targetX;
    int targetY;
    double g;

public:
    Node(int _locationX, int _locationY, int _targetX, int _targetY, std::shared_ptr<Node> previous_ptr = nullptr);

    int getX() const {
        return locationX;
    }

    int getY() const {
        return locationY;
    }

    double getH() const{
        return sqrt(pow(abs(locationX - targetX), 2) + pow(abs(locationY - targetY), 2));
    }

    double getG() const{
        return g;
    }

    void setG(double value) {
        g = value;
    }

    double getF() const {
        return getG() + getH();
    }

    std::shared_ptr<Node> getPrevious() {
        return previous;
    }

    void setPrevious(std::shared_ptr<Node> node) {
        previous = node;
    }

};

bool operator==(const Node& node, const Node& other);
#endif //FANTASYRPG_NODE_H
