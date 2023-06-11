#ifndef FANTASYRPG_MOCKPLAYER_H
#define FANTASYRPG_MOCKPLAYER_H
#include <string>

class MockPlayer {
private:
public:
    int money;
    int xp;
    int levelxp;
    int hp;
    static char symbol;

    int locationX, locationY;

    MockPlayer(): money{100}, xp{0}, levelxp{10}, hp{100}, locationX{100}, locationY{100} {};

    static char getSymbol() {return symbol;}

    void setLocation(int newLocationX, int newLocationY) {
        locationX = newLocationX;
        locationY = newLocationY;
    }
};

#endif //FANTASYRPG_MOCKPLAYER_H
