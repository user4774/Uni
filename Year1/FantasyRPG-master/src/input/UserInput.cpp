//
// Created by J on 2/21/2021.
//
#include "UserInput.h"

void Input::userInput(TileMap tileMap, MockPlayer& player) {
    switch (_getch()) {
        case 119:
            tileMap.up(player);
            break;
        case 115:
            tileMap.down(player);
            break;
        case 97:
            tileMap.left(player);
            break;
        case 100:
            tileMap.right(player);
            break;
    }
}
