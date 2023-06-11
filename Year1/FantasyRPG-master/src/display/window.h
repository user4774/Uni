#ifndef WINDOW_H
#define WINDOW_H

#include<iostream>
#include<string>
#include<windows.h>

class Window {

    public:
        Window();
        Window(COORD, int, int, bool);

        void drawBorder();
        void paintWindow();
        void setTopLeft(COORD);
        void setWidth(int);
        void setHeight(int);
        void setBorder(int);
        void setHandle(HANDLE);

    private:
        COORD topLeft;
        int width;
        int height;
        bool border;
        HANDLE hStdOut;

};

#endif
