#include "window.h"

Window::Window() {

}

Window::Window(COORD _topleft, int _width, int _height, bool _border)
    : topLeft{_topleft},
      width{_width},
      height{_height},
      border{_border},
      hStdOut{GetStdHandle(STD_OUTPUT_HANDLE)}
      {drawBorder(),
      paintWindow();}

void Window::drawBorder() {

    SetConsoleCursorPosition(hStdOut, topLeft);
    COORD cursorPos;

    std::string horizontalBar(width - 2, '-');
    horizontalBar = '+' + horizontalBar + '+';
    std::cout << horizontalBar;

    for (int i = 0; i < 2; i++) {
        for (int j = 1; j < height - 1; j++) {
            if (i == 0) {
                cursorPos.X = topLeft.X;
            } else {
                cursorPos.X = topLeft.X + width - 1;
            }
            cursorPos.Y = topLeft.Y + j;
            SetConsoleCursorPosition(hStdOut, cursorPos);
            std::cout << "|";
        }
        SetConsoleCursorPosition(hStdOut, cursorPos);
    }

    cursorPos.X = topLeft.X;
    cursorPos.Y = topLeft.Y + height - 1;
    SetConsoleCursorPosition(hStdOut, cursorPos);
    std::cout << horizontalBar;
}

void Window::paintWindow() {

    COORD cursorPos;
    cursorPos.X = topLeft.X + 1;
    cursorPos.Y = topLeft.Y + 1;
    SetConsoleCursorPosition(hStdOut, cursorPos);

    for (int i = 0; i < height - 1; i++) {
        for (int j = 0; j < width - 2; j++) {
            std::cout << " ";
        }
        cursorPos.X = topLeft.X + 1;
        cursorPos.Y = topLeft.Y + i + 1;
        SetConsoleCursorPosition(hStdOut, cursorPos);
    }
};


void Window::setTopLeft(COORD _topLeft) {
    topLeft = _topLeft;
}

void Window::setWidth(int _width) {
    width = _width;
}

void Window::setHeight(int _height) {
    height = _height;
}

void Window::setBorder(int _border) {
    border = _border;
}

void Window::setHandle(HANDLE _hStdOut) {
    hStdOut = _hStdOut;
}

