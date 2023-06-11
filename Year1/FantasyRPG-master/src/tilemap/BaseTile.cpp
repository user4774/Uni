//
// Created by J on 3/16/2021.
//

#include "BaseTile.h"

BaseTile::BaseTile(int _locationX, int _locationY, bool _passable, bool _conditional) {
    locationX = _locationX;
    locationY = _locationY;
    passable = _passable;
    conditional = _conditional;
}
