#include <iostream>
#include <utility>
#include "Items.h"
using namespace std;

Items::Items(string nam, string des, int x, int y, int wei, int pri, int dur) { // implementation of constructor

    name = nam;
    description = des;
    location = std::make_pair(x, y);
    weight = wei;
    price = pri;
    duration = dur;
};