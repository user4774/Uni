#include "tilemap.h"

TileMap::TileMap(int _maxHeight, int _maxWidth) {
    maxHeight = _maxHeight;
    maxWidth = _maxWidth;
}

void TileMap::createMap() {
    this->tileMap.reserve(maxHeight * maxWidth);
    for (int y = 0; y < maxHeight; ++y) {
        for (int x = 0; x < maxWidth; ++x) {
            if (y == 0 || y == maxHeight - 1 || x == 0 || x == maxWidth - 1) {
                Tile testTile = Tile('#', x, y, false);
                this->tileMap.push_back(testTile);
            } else if (y == 25 && x == 25){
                Tile testTile = Tile('#', x, y, false);
                this->tileMap.push_back(testTile);
            } else if (y == 26 && x == 26){
                Tile testTile = Tile('#', x, y, false);
                this->tileMap.push_back(testTile);
            } else {
                Tile testTile = Tile('.', x, y, true);
                this->tileMap.push_back(testTile);
            }
        }
    }
}

void TileMap::cursorPosition(int x, int y) {
    HANDLE getHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(getHandle, coord);
}

void TileMap::placeEnemies() {
    for (MockEnemy* enemy : MockEnemy::getEnemies()) {
        cursorPosition(enemy->getLocationX(), enemy->getLocationY());
        std::cout << enemy->getSymbol();
    }
}

void TileMap::drawMap(MockPlayer mockPlayer){
    system("cls");
    for (const Tile& tile : this->tileMap) {
        if (mockPlayer.getLocationY() * maxWidth + mockPlayer.getLocationX() ==
        (tile.getLocationY() * maxWidth + tile.getLocationX())) {
            std::cout << mockPlayer.getSymbol();
        } else if (((tile.getLocationY() * maxWidth + tile.getLocationX()) + 1) % maxWidth == 0) {
            std::cout << tile.getSymbol() << std::endl;
        } else {
            std::cout << tile.getSymbol();
        }
    }
    placeEnemies();
}

void TileMap::move(Entity* entity, int newX, int newY) {
    if (newX > 0 && newY > 0) {
        if (this->tileMap[newY * this->getWidth() + newX].isPassable()) {
            cursorPosition(entity->getLocationX(), entity->getLocationY());
            std::cout << this->tileMap[entity->getLocationY() * this->getWidth() + entity->getLocationX()].getSymbol();
            entity->setLocationX(newX);
            entity->setLocationY(newY);
            cursorPosition(newX, newY);
            std::cout << entity->getSymbol();
        }
    }
}

void TileMap::moveEnemies(MockEnemy& enemy, MockPlayer& player, int newX, int newY) {
    if (newX > 0 && newY > 0) {
        if (this->tileMap[newY * this->getWidth() + newX].isPassable()) {
            if (newX == player.getLocationX() && newY == player.getLocationY()) {
                //fight
                return;
            }
            cursorPosition(enemy.getLocationX(), enemy.getLocationY());
            std::cout << this->tileMap[enemy.getLocationY() * this->getWidth() + enemy.getLocationX()].getSymbol();
            enemy.setLocationX(newX);
            enemy.setLocationY(newY);
            cursorPosition(newX, newY);
            std::cout << enemy.getSymbol();
        }
    }
}
