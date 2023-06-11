/**
 * @file window.h
 * @author James Askew
 * @brief 
 * @version 0.1
 * @date 2021-03-07
 * 
 * references:
 * http://www.winprog.org/tutorial/start.html
 * https://youtu.be/ssGka-bSTvQ
 * https://youtube.com/playlist?list=PL7Ej6SUky135IAAR3PFCFyiVwanauRqj3
 * 
 */

#ifndef WINDOW_CLASS_H
#define WINDOW_CLASS_H

#ifndef UNICODE
#define UNICODE
#endif

#include<windows.h>

class Window {

    protected:
        HWND m_hwnd;
        bool gameRunning;

    public:
        Window();
        bool init();    // initialise the window
        bool release();    // release the window
        bool broadcast();
        bool isRunning();
        ~Window();

    // events
    virtual void onCreate() = 0;
    virtual void onUpdate() = 0;
    virtual void onDestroy();

  };

#endif