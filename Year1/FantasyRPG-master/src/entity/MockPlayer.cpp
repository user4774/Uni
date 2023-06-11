//
// Created by J on 2/21/2021.
//

#include "MockPlayer.h"

MockPlayer::MockPlayer(int _hp, char _symbol, int _locationX, int _locationY)  : Entity(_symbol, _locationX, _locationY) {
    hp = _hp;
}
