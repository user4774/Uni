#ifndef FANTASYRPG_MOCKENEMY_H
#define FANTASYRPG_MOCKENEMY_H
#include <vector>
#include "Entity.h"

class MockEnemy: public Entity {
private:
    int hp;
    static std::vector<MockEnemy*> enemies;

public:
    MockEnemy(int _hp, char _symbol, int _locationX, int _locationY);

    ~MockEnemy() {};

    static std::vector<MockEnemy*> getEnemies() {
        return enemies;
    }


};

#endif //FANTASYRPG_MOCKENEMY_H
