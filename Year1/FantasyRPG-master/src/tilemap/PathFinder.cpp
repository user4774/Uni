#include "PathFinder.h"

Node PathFinder::findPath(int sourceX, int sourceY, int destinationX, int destinationY, TileMap& tileMap) {
    Node source(sourceX, sourceY, destinationX, destinationY);
    open.push_back(source);

    while (!open.empty()) {
        std::shared_ptr<Node> current = std::make_shared<Node>(optimalStep(open));
        closed.push_back(current->getY() * tileMap.getWidth() + current->getX());

        for (int y = current->getY() - 1; y < current->getY() + 2; ++y) {
            for (int x = current->getX() - 1; x < current->getX() + 2; ++x) {
                Node neighbour(x, y, destinationX, destinationY, current);

                if (isValid(x, y, tileMap)) {
                    if (neighbour.getX() == destinationX && neighbour.getY() == destinationY) {
                        return neighbour;
                    }

                    auto itClosed = std::find(closed.begin(), closed.end(), y * tileMap.getWidth() + x);

                    if (itClosed == closed.end()) {
                        auto itOpen = std::find(open.begin(), open.end(), neighbour);

                        if (itOpen == open.end()) {
                            open.emplace_back(x, y, destinationX, destinationY, current);
                        } else if (itOpen != open.end()) {
                            if (itOpen->getG() > neighbour.getG()) {
                                itOpen->setG(neighbour.getG());
                                itOpen->setPrevious(neighbour.getPrevious());
                            }
                        }
                    }
                }
            }
        }
    }
    return source;
}

Node PathFinder::getPath(Node& node) {
    Node newNode = node;
    Node answer = node;
    while (newNode.getPrevious() != nullptr) {
        newNode = *newNode.getPrevious();
        if ((newNode.getPrevious() != nullptr) && (newNode.getPrevious()->getPrevious() == nullptr)) {
            answer = newNode;
        }
    }
    return answer;
}

Node PathFinder::optimalStep(std::vector<Node>& nodes) {
    auto it = std::min_element(nodes.begin(), nodes.end(), [] (const Node& first, const Node& second) {
        return (first.getF() < second.getF()) || (first.getF() == second.getF() && first.getH() < second.getH());});
    Node node = *it;
    nodes.erase(it);
    return node;
}

bool PathFinder::isValid(int x, int y, TileMap& tileMap) {
    if (!tileMap.tileMap[y * tileMap.getWidth() + x].isPassable()) {
        return false;
    }

    for (MockEnemy* enemy : MockEnemy::getEnemies()) {
        if (enemy->getLocationX() == x && enemy->getLocationY() == y) {
            return false;
        }
    }

    if (y < 0 || y > tileMap.getHeight() || x < 0 || x > tileMap.getWidth()) {
        return false;
    }
    return true;
}
