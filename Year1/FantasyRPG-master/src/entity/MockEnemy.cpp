#include "MockEnemy.h"

MockEnemy::MockEnemy(int _hp, char _symbol, int _locationX, int _locationY)  : Entity(_symbol, _locationX, _locationY) {
    hp = _hp;
    enemies.push_back(this);
}

std::vector<MockEnemy*> MockEnemy::enemies;
