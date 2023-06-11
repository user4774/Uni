#ifndef FANTASYRPG_PATHFINDER_H
#define FANTASYRPG_PATHFINDER_H
#include <vector>
#include <set>
#include <algorithm>
#include <tuple>
#include "Node.h"
#include "tilemap.h"
#include "../entity/MockEnemy.h"

class PathFinder {
    std::vector<int> closed;
    std::vector<Node> open;

    static Node optimalStep(std::vector<Node>& node);

    static bool isValid(int x, int y, TileMap& tileMap);

public:
    PathFinder() {};
    Node findPath(int sourceX, int sourceY, int destinationX, int destinationY, TileMap& tileMap);

    static Node getPath(Node& node);
};


#endif //FANTASYRPG_PATHFINDER_H
