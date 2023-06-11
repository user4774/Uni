/**
 * @file placeholder_creature_classes.cpp
 * @author James Askew
 * @brief This file holds placeholder classes written to allow unit testing prior to integration with others' work.
 * @version 0.1
 * @date 2021-02-28
 * 
 */
#ifndef creature_HEADER
#define creature_HEADER

#include<iostream>
#include<vector>
#include "container.h"

class Creature {

    public:
        static std::vector<Creature*> creatureList;
        std::string name;
        Container inventory;
        Creature(std::string);
};

#endif