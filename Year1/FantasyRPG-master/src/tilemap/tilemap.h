#ifndef FANTASYRPGTEMP_TILEMAP_H
#define FANTASYRPGTEMP_TILEMAP_H
#include <Windows.h>
#include <vector>
#include <iostream>
#include <utility>
#include <tuple>
#include "tile.h"
#include "../entity/MockEnemy.h"
#include "../entity/MockPlayer.h"

class PathFinder;

class TileMap {
private:
    int maxHeight;
    int maxWidth;
public:
    std::vector<Tile> tileMap;

    TileMap(int maxHeight, int maxWidth);

    void createMap();

    int getHeight() const {return maxHeight;}

    int getWidth() const {return maxWidth;}

    static void placeEnemies();

    void drawMap(MockPlayer mockPlayer);

    void move(Entity* entity, int newX, int newY);

    void TileMap::moveEnemies(MockEnemy& enemy, MockPlayer& player, int newX, int newY);

    static void cursorPosition(int x, int y);
};

#endif //FANTASYRPGTEMP_TILEMAP_H
