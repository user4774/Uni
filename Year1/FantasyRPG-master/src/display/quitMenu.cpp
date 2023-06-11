/**
 * @file mainMenu.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-03-11
 * 
 * https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
 * 
 */

#include<conio.h>
#include "quitMenu.h"

QuitMenu::QuitMenu()
    : Menu("Are you sure you want to quit?", {"Quit", "Cancel"})
    {init();}

int QuitMenu::selectOption() {

    bool selected = false;

    while(!selected){
        switch(getch()){
            case 72:
            case 87:
            case 119:
            case 80:
            case 83:
            case 115:
            /**
             * @brief moving up or down wraps so always swaps
             * 
             */
                if (highlightedOption == 0) {
                    highlightedOption = 1;
                } else {
                    highlightedOption = 0;
                }
                printOptions();
                break;

            case 8:
            case 27: {
            /**
             * @brief escape or backspace keys to quit
             * 
             */
                selected = true;
                highlightedOption = 1;
                break;
            }

            case 13:
            case 32:
                if (highlightedOption == 0) {
                    SendMessage(GetConsoleWindow(), WM_CLOSE, 0, 0);
                } else {
                    selected = true;
                    break;
                }
        }
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    return highlightedOption;
}

void QuitMenu::init() {
    formatMainText();
    createWindow();
    printMainText();
    printOptions();
    selectOption();
}

void QuitMenu::refresh() {
    highlightedOption = 0;
    createWindow();
    printMainText();
    printOptions();
    selectOption();
}