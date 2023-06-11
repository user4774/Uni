#include "placeholder_player.h"

MockPlayer::MockPlayer(int _money, int _xp, int _hp, int _locationX, int _locationY) {
    money = _money;
    xp = _xp;
    hp = _hp;
    locationX = _locationX;
    locationY = _locationY;
}

char MockPlayer::symbol = '@';
