/**
 * @file placeholder_item_classes.h
 * @author James Askew
 * @brief Placeholder classes for Items
 * @version 0.1
 * @date 2021-02-28
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef item_HEADER
#define item_HEADER

#include<iostream>
#include<string>

class Item {
    public:
        std::string name;

        Item(std::string n);
        virtual int getAccessCode() {return -1;}

        bool operator== (const Item &other) const {return name == other.name;}
};

class Key : public Item {
    
    private:
        int accessCode;

    public:
        Key(int code);
        virtual int getAccessCode() {return accessCode;}
};

#endif
