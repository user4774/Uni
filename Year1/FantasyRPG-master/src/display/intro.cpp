//https://www.w3schools.com/cpp/cpp_files.asp
// #define _WIN32_WINNT 0x0500

#include<iostream>
#include<string>
#include<fstream>
#include<thread>
#include<chrono>
#include<conio.h>
#include<stdio.h>
#include<windows.h>
#include<iomanip>
#include "console.h"

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void intro() {

    // Create a text string, which is used to output the text file
    std::string printString;

    // Read from the text file
    std::ifstream introText("intro.txt");

    int lineNo = 0;


    for (int i = 0; i < 25; i++) {
        std::cout << "\n";
    }
    while (getline(introText, printString)) {
        if (lineNo == 5) {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        } else if (lineNo == 11) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            ClearScreen();
            for (int i = 0; i < 16; i++) {
                std::cout << "\n";
            }
        } else if (lineNo == 11 | lineNo == 19 | lineNo == 30) {
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
        }
        std::cout << printString << std::endl;
        lineNo++;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    std::cout << "\n\n\n\n\n";

    for (int i = 0; i < 83; i++) {
        std::cout << " ";
    }

    std::string pressKey = "Press any key to continue...";

    for (char i: pressKey) {
        std::cout << i;
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    
    // Close the file
    introText.close();

    getch();

    ClearScreen();

}
