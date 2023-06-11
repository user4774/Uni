//
// Created by J on 4/15/2021.
//
#include "GameInstance.h"

void GameInstance::Run() {
    MockPlayer player(100, '@', 2, 2);
    MockEnemy enemy1(25, '&', 30, 35);
    MockEnemy enemy2(25, '&', 2, 35);
    TileMap tileMap(50, 50);
    tileMap.createMap();

    tileMap.drawMap(player);

    while (running) {
        HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO info;
        info.dwSize = 100;
        info.bVisible = FALSE;
        SetConsoleCursorInfo(consoleHandle, &info);
        userInput(tileMap, player);
    }
}

void GameInstance::userInput(TileMap tileMap, MockPlayer &player) {
    switch (_getch()) {
        case 119:
            tileMap.move(&player, player.getLocationX(), player.getLocationY() - 1);
            enemyTurn(tileMap, player);
            break;
        case 115:
            tileMap.move(&player, player.getLocationX(), player.getLocationY() + 1);
            enemyTurn(tileMap, player);
            break;
        case 97:
            tileMap.move(&player, player.getLocationX() - 1, player.getLocationY());
            enemyTurn(tileMap, player);
            break;
        case 100:
            tileMap.move(&player, player.getLocationX() + 1, player.getLocationY());
            enemyTurn(tileMap, player);
            break;
        case 27:
            running = false;
            cleanConsole();
            break;
    }
}

void GameInstance::cleanConsole() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 1;
    info.bVisible = TRUE;
    SetConsoleCursorInfo(consoleHandle, &info);
    system("cls");
}

bool GameInstance::running = true;

void GameInstance::enemyTurn(TileMap tileMap, MockPlayer player) {
    for (MockEnemy* enemy : MockEnemy::getEnemies()) {
        PathFinder pathFinder;
        Node node = pathFinder.findPath(enemy->getLocationX(),
                                        enemy->getLocationY(), player.getLocationX(), player.getLocationY(), tileMap);
        Node step = PathFinder::getPath(node);
        tileMap.moveEnemies(*enemy, player, step.getX(), step.getY());
    }
}
