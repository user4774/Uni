/**
 * @file containers.cpp
 * @author James Askew
 * @brief Base class containers
 * @version 0.1
 * @date 2021-02-18
 * 
 */
#include<iostream>
#include<string>
#include "container.h"

Container::Container(std::string n, std::string desc)
    : name{n},
      description{desc}
      {};

Item* Container::getItem(int index) {
    if (!contents.empty()) {
        return getContents()[index];
    }
}

void Container::addItem(Item* item) {
    contents.push_back(item);
}

void Container::removeItem(int index) {
    if (!contents.empty()) {
        contents.erase(contents.begin() + index);
    }
}
