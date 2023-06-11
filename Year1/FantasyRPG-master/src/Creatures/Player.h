#pragma once
#include "Humanoids.h"
class Player :
    public Humanoids
{
public:
    Player()
    {
        health = 100;
        attack = 10;
        defence = 5;
    }
    //this should be protected 
private:
    int money;
    int xp;
    int levelUpXp;

    void levelUp(int level);
};

