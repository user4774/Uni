#include "placeholder_item_classes.h"
#include<vector>

Item::Item(std::string n) {
    name = n;
}

Key::Key(int code) : accessCode{code}, Item("key") {};

