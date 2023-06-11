//
// Created by J on 2/21/2021.
//
#ifndef FANTASYRPG_USERINPUT_H
#define FANTASYRPG_USERINPUT_H
#include <conio.h>
#include "../tilemap/tilemap.h"
#include "../player/MockPlayer.h"

class Input {
public:
    static void userInput(TileMap tileMap, MockPlayer& player);
};

#endif //FANTASYRPG_USERINPUT_H
