/**
 * @file player_inventory.cpp
 * @author James Askew
 * @brief Source file for player_inventory class
 * @version 0.1
 * @date 2021-02-18
 * 
 */
#include<iostream>
#include<memory>
#include "chest.h"
#include "placeholder_creature_classes.h"

Chest::Chest(std::string n, std::string desc, bool acc): Container(n, desc), accessible{acc} {
    if (acc == false) {
        if (Creature::creatureList.size() > 0) {
            int code = std::rand();
            accessCode = code;
            Key* key = new Key(code);
            Creature::creatureList[std::rand() % Creature::creatureList.size()]->inventory.addItem(key);
        } else { 
            accessible = true;
        }
    }
};

Item* Chest::getItem(int index) {
    if (getAccessible() && !contents.empty()) {
        return getContents()[index];
    }
}

std::vector<Item*> Chest::getContents() {
    if (!getAccessible()){
        throw Locked(); // look to produce 
    } else {
        return contents;
    }
}

void Chest::unlock(int keyCode) {
    if (keyCode == getAccessCode()) {
        accessible = true;
    }
}

void Chest::addItem(Item* item) {
    if (!getAccessible()){
        throw std::exception();
    } else {
        contents.push_back(item);
    }
}

void Chest::removeItem(int index) {
    if (!getAccessible()){
        throw std::exception();
    } else if (!contents.empty()) {
        contents.erase(contents.begin() + index);
    }
}

const char* Chest::Locked::what() const throw() {
    return "This is locked!";
}
