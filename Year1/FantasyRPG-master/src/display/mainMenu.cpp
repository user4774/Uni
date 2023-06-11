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

#include<fstream>
#include<array>
#include<conio.h>
#include "mainMenu.h"
#include "quitMenu.h"
#include "window.h"

MainMenu::MainMenu()
    : Menu("", {"New Game", "Quit"})
    {init();}

void MainMenu::formatMainText() {

    std::ifstream fileText("mainMenu.txt");

    std::string fileLine;

    while (getline(fileText, fileLine)) {
        mainText += fileLine + '\n';
    }
}

void MainMenu::createWindow() {

    CONSOLE_SCREEN_BUFFER_INFO screenBuffer;
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hStdOut, &screenBuffer);

    int width = screenBuffer.dwSize.X / 6.14 - 5;   // 195 - one character is ~6.14 pixels wide -5 is to mirror space lost to scroll bar
    int height = screenBuffer.dwSize.Y / 12.62;    // 63 - one character is ~12.62 pixels tall

    COORD topLeft;
    topLeft.X = 4;
    topLeft.Y = 0;

    Window window(topLeft, width, height, true);
}


void MainMenu::printMainText() {

    int avLineLength = 0;
    int thisLineLength = 0;
    int noLines = 0;

    for (int i = 0; i < mainText.size(); i++) {
        ++thisLineLength;
        if (mainText[i] == '\n') {
            ++noLines;
            avLineLength += thisLineLength;
            thisLineLength = 0;
        }
    }

    avLineLength = avLineLength / noLines;

    CONSOLE_SCREEN_BUFFER_INFO screenBuffer;
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hStdOut, &screenBuffer);

    int screenWindowWidth = screenBuffer.dwSize.X / 6.14;
    int screenWindowHeight = screenBuffer.dwSize.Y / 12.62;

    COORD cursorPos;
    cursorPos.X = screenWindowWidth / 2 - avLineLength / 2;
    cursorPos.Y = screenWindowHeight / 4 - noLines / 2;
    SetConsoleCursorPosition(hStdOut, cursorPos);
    int j = 1;

    for (int i = 0; i < mainText.size(); i++) {
        std::cout << mainText[i];
        if (mainText[i] == '\n') {
            cursorPos.Y = screenWindowHeight / 4 - noLines / 2 + j;
            SetConsoleCursorPosition(hStdOut, cursorPos);
            ++j;
        }
    }
}

int MainMenu::selectOption() {

    bool selected = false;
    int bottomOption = options.size() - 1;

    while(!selected){
        switch(getch()){
            case 72:
            case 87:
            case 119:
            /**
             * @brief up-arrow / w / W is pressed, move up
             * 
             */
                if (highlightedOption == 0) {
                    highlightedOption = bottomOption;
                } else {
                    highlightedOption--;
                }
                printOptions();
                break;

            case 80:
            case 83:
            case 115:
            /**
             * @brief down-arrow / s / S is pressed, move down
             * 
             */
                if (highlightedOption == bottomOption) {
                    highlightedOption = 0;
                } else {
                    highlightedOption++;
                }
                printOptions();
                break;

            case 8:
            case 27: {
            /**
             * @brief escape or backspace keys to quit returns -1 to reflect that this is not an option
             * 
             */
                QuitMenu quitMenu;
                refreshMenu();
                break;
            }

            case 13:
            case 32:
                selected = true;
                break;
        }
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    return highlightedOption;
}

void MainMenu::init() {
    formatMainText();
    createWindow();
    printMainText();
    printOptions();
    switch (selectOption()) {
        case 0:
            break;
        case 1:
            QuitMenu quitMenu;
            refreshMenu();
            break;
    }
    getch();
}

void MainMenu::refreshMenu() {
    highlightedOption = 0;
    createWindow();
    printMainText();
    printOptions();
    switch (selectOption()) {
        case 0:
            break;
        case 1:
            QuitMenu quitMenu;
            refreshMenu();
            break;
    }
}

void MainMenu::refreshOptions() {
    highlightedOption = 0;
    printOptions();
    switch (selectOption()) {
        case 0:
            break;
        case 1:
            QuitMenu quitMenu;
            refreshMenu();
            break;
    }
}
