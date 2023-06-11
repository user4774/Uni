//
// Created by J on 3/16/2021.
//

#ifndef FANTASYRPG_BASETILE_H
#define FANTASYRPG_BASETILE_H


class BaseTile {
protected:
    int locationX, locationY;
    bool passable;
    bool conditional;

    BaseTile(int _locationX, int _locationY, bool _passable, bool _conditional);

    int get_location_X() const {
        return locationX;
    }

    int get_location_Y() const {
        return locationY;
    }

    bool is_passable() const {
        return passable;
    }

    bool is_conditional() const {
        return conditional;
    }
};


#endif //FANTASYRPG_BASETILE_H
