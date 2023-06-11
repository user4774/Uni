#include "tile.h"

Tile::Tile(char _symbol, int _locationX, int _locationY, bool _passable) {
    symbol = _symbol;
    locationX = _locationX;
    locationY = _locationY;
    passable = _passable;
}
