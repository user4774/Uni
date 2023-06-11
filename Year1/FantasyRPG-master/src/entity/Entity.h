//
// Created by J on 4/15/2021.
//

#ifndef FANTASYRPG_ENTITY_H
#define FANTASYRPG_ENTITY_H

class Entity {
private:
    char symbol;
    int locationX, locationY;

public:

    Entity(char _symbol, int _locationX, int _locationY);

    virtual ~Entity() {};

    int getLocationX() {
        return locationX;
    }

    int getLocationY() {
        return locationY;
    }

    void setLocationX(int x) {
        locationX = x;
    }

    void setLocationY(int y) {
        locationY = y;
    }

    char getSymbol() {
        return symbol;
    }

};


#endif //FANTASYRPG_ENTITY_H
