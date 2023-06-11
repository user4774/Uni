#ifndef MAINMENU_H
#define MAINMENU_H

#include "menu.h"

class MainMenu : public Menu {
    public:
        MainMenu();
        void formatMainText();
        void createWindow();
        void printMainText();
        int selectOption();
        void init();
        void refreshMenu();
        void refreshOptions();

};

#endif