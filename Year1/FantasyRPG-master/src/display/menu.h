#ifndef MENU_H
#define MENU_H

#include<iostream>
#include<string>
#include<vector>
#include "window.h"

class Menu {
    protected:
        std::string mainText;
        std::vector<std::string> options;
        int highlightedOption;

    public:
        Menu(std::string, std::vector<std::string>);

        virtual void formatMainText();
        virtual void createWindow();
        virtual void printMainText();
        void printOptions();
        virtual int selectOption();

        int getOption() {return highlightedOption;}
        virtual void init();
        virtual void refresh();
};

#endif

/**-----------------
 * <blank line>
 * <blank line>
 * <main text>
 * <blank line>
 * <blank line>
 * <option> - middle of screen
 * <blank line>
 * ----------------------
 */