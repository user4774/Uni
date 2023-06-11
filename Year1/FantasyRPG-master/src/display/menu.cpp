#include<cmath>
#include<conio.h>
#include "menu.h"

Menu::Menu(std::string _mainText, std::vector<std::string> _options)
/**
 * @brief 
 * 
 */
    : mainText{_mainText},
      options{_options},
      highlightedOption{0}
      {}

void Menu::formatMainText() {

    CONSOLE_SCREEN_BUFFER_INFO screenBuffer;
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hStdOut, &screenBuffer);

    float displayWindowX = screenBuffer.dwSize.X / 6.14;    // 195 - one character is ~6.14 pixels wide
    float displayWindowY = screenBuffer.dwSize.Y / 12.62;    // 63 - one character is ~12.62 pixels tall

    int mainTextLength = mainText.size();
    int noOptions = options.size();
    float noLines = ceil(mainTextLength / (displayWindowX / 3) );

    if (mainTextLength > displayWindowX / 3) {
        for (int i = 1; i < noLines; i++) {
            for (int j = (mainTextLength / noLines) * i; j < mainTextLength; j++) {
                if (mainText[j] == ' ') {
                    mainText.replace(j, 1, "\n");
                    break;
                }
            }
        }
    }
}

void Menu::createWindow() {

    CONSOLE_SCREEN_BUFFER_INFO screenBuffer;
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hStdOut, &screenBuffer);

    float displayWindowX = screenBuffer.dwSize.X / 6.14;    // 195 - one character is ~6.14 pixels wide
    float displayWindowY = screenBuffer.dwSize.Y / 12.62;    // 63 - one character is ~12.62 pixels tall

    int mainTextLength = mainText.size();
    int noOptions = options.size();
    float noLines = ceil(mainTextLength / (displayWindowX / 3) );
    int width;

    if (mainTextLength > displayWindowX / 3) {
        width = (mainTextLength / noLines) * 1.5;
    } else {
        width = mainTextLength * 1.5;
    }

    int height;

    height = noLines + 2 * noOptions + 6;

    COORD topLeft;
    topLeft.X = (displayWindowX - width) / 2;
    topLeft.Y = (displayWindowY - height) / 2;

    Window window(topLeft, width, height, true);
}

void Menu::printMainText() {

    CONSOLE_SCREEN_BUFFER_INFO screenBuffer;
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hStdOut, &screenBuffer);

    float displayWindowX = screenBuffer.dwSize.X / 6.14;    // 195 - one character is ~6.14 pixels wide
    float displayWindowY = screenBuffer.dwSize.Y / 12.62;    // 63 - one character is ~12.62 pixels tall
    int mainTextLength = mainText.size();

    COORD textOrigin;

    if (mainTextLength > displayWindowX / 3) {
        for (int i = 0; i < mainTextLength; i++) {
            if (mainText[i] == '\n') {
                textOrigin.X = displayWindowX / 2 - i / 2;
                break;
            }
        }
    } else {
        textOrigin.X = displayWindowX / 2 - mainTextLength / 2;
    }

    int noLines = mainTextLength / (displayWindowX / 3);

    textOrigin.Y = displayWindowY / 2 - noLines - 3;

    SetConsoleCursorPosition(hStdOut, textOrigin);

    int j = 1;

    for (int i = 0; i < mainTextLength; i++) {
        std::cout << mainText[i];
        if (mainText[i] == '\n') {
            textOrigin.Y = displayWindowY / 2 - noLines - 2 + j;
            SetConsoleCursorPosition(hStdOut, textOrigin);
            ++j;
        }
    }
}

void Menu::printOptions() {

    CONSOLE_SCREEN_BUFFER_INFO screenBuffer;
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hStdOut, &screenBuffer);

    float displayWindowX = screenBuffer.dwSize.X / 6.14;    // 195 - one character is ~6.14 pixels wide
    float displayWindowY = screenBuffer.dwSize.Y / 12.62;    // 63 - one character is ~12.62 pixels tall
    int mainTextLength = mainText.size();
    int noOptions = options.size();
    float noLines = ceil(mainTextLength / (displayWindowX / 3) );

    COORD textOrigin;
    
    textOrigin.X = displayWindowX / 2 - 4;
    for (int i = 0; i < options.size(); i++) {
        textOrigin.Y = displayWindowY / 2 + 2 * i;
        SetConsoleCursorPosition(hStdOut, textOrigin);
        if (i == highlightedOption) {
            SetConsoleTextAttribute(hStdOut, 143);
        } else {
            SetConsoleTextAttribute(hStdOut, 15);
        }
        std::cout << options[i];
    }
    SetConsoleCursorPosition(hStdOut, textOrigin);
}

int Menu::selectOption() {

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
                highlightedOption = -1;
                selected = true;
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

void Menu::init() {
    formatMainText();
    createWindow();
    printMainText();
    printOptions();
}

void Menu::refresh() {
    highlightedOption = 0;
    createWindow();
    printMainText();
    printOptions();
    selectOption();
}