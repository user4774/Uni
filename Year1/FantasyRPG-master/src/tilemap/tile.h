#ifndef FANTASYRPGTEMP_TILE_H
#define FANTASYRPGTEMP_TILE_H
#include <string>
#include <utility>
#include <iostream>

class Tile {
private:
    char symbol;
    int locationX, locationY;
    bool passable;

public:
    Tile(char _symbol, int _locationX, int _locationY, bool _passable);

    char getSymbol() const {
        return symbol;
    }

    int getLocationX() const {
        return locationX;
    }

    int getLocationY() const {
        return locationY;
    }

    bool isPassable() const {
        return passable;
    }

    bool operator==(const Tile& other) const {
        if (this->getLocationY() == other.getLocationY() && this->getLocationX() == other.getLocationX() &&
            this->getSymbol() == other.getSymbol()) {
            return true;
        }
        return false;
    }
};

#endif //FANTASYRPGTEMP_TILE_H
