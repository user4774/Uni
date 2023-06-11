//
// Created by J on 2/21/2021.
//

#ifndef FANTASYRPG_MOCKPLAYER_H
#define FANTASYRPG_MOCKPLAYER_H
#include "Entity.h"
#include <string>

class MockPlayer : public Entity{
private:
    int hp;

public:
    MockPlayer(int _hp, char _symbol, int _locationX, int _locationY);

    ~MockPlayer() {};
};

#endif //FANTASYRPG_MOCKPLAYER_H
