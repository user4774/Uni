/**
 * @file player_inventory.h
 * @author James Askew
 * @brief chests class header file.
 * @version 0.1
 * @date 2021-02-18
 * 
 */
#ifndef chest_HEADER
#define chest_HEADER

#include "container.h"

/**
 * @brief Placeholder class to aid in testing.
 * 
 */


class Chest : public Container {

    private:
        bool accessible;
        int accessCode;

    public:
        Chest(std::string, std::string, bool);
        bool getAccessible() {return accessible;}
        int getAccessCode() {return accessCode;}
        Item* getItem(int index);
        std::vector<Item*> getContents();


        void unlock(int keyCode);

        void addItem(Item* item);
        void removeItem(int index);

        class Locked : public std::exception {
            /**
             * @brief This exception will be thrown if a locked container is attempted to be accessed.
             * 
             * @return const char* 
             */
            public:
                const char * what () const throw ();
        };
};

#endif
