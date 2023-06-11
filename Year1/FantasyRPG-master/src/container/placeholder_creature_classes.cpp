#include "placeholder_creature_classes.h"
#include<vector>

Creature::Creature(std::string n) : name{n}, inventory{"creature", "inventory"} {
    creatureList.push_back(this);
};

std::vector<Creature*> Creature::creatureList;
