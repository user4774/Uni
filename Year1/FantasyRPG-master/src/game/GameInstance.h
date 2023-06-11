//
// Created by J on 4/15/2021.
//

#ifndef FANTASYRPG_GAMEINSTANCE_H
#define FANTASYRPG_GAMEINSTANCE_H
#include <conio.h>
#include "../tilemap/PathFinder.h"
#include "../entity/MockPlayer.h"
#include "../entity/MockEnemy.h"
#include "../tilemap/tilemap.h"

class GameInstance {
private:
    static bool running;

    void userInput(TileMap tileMap, MockPlayer& player);

    void cleanConsole();

    void enemyTurn(TileMap tileMap, MockPlayer player);

public:
    void Run();
};


#endif //FANTASYRPG_GAMEINSTANCE_H
