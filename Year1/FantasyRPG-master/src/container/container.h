/**
 * @file containers.h
 * @author James Askew
 * @brief Containers base class declarations header file
 * @version 0.1
 * @date 2021-02-18
 * 
 */
#ifndef container_HEADER
#define container_HEADER

#include<iostream>
#include<string>
#include<vector>
#include "placeholder_item_classes.h"

/**
 * @brief Container base class used for literal containers - inventories, merchants, etc.
 * 
 */
class Container {

    protected:
        std::string name;
        std::string description;
        std::vector<Item*> contents;

    public:
        Container(std::string, std::string);

        std::string& getName() {return name;}
        std::string& getDescription() {return description;}
        Item* getItem(int index);
        std::vector<Item*> getContents() {return contents;}

        void addItem(Item* item);
        void removeItem(int index);

};

#endif
