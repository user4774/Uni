#include<string>
#include "appWindow.h"

AppWindow::AppWindow() {
}

AppWindow::~AppWindow() {
}

void AppWindow::onCreate() {
    Window::onCreate();
}

void AppWindow::onUpdate() {
    Window::onUpdate();
}

void AppWindow::onDestroy() {
    Window::onDestroy();
}

void AppWindow::OnPaint() {
    
}

void AppWindow::introWindow() {
    {
        PAINTSTRUCT ps;
        HDC hdc = ::BeginPaint(m_hwnd, &ps);
        HDC hdc_x = CreateCompatibleDC(NULL);
        HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, L"intro_background.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE); //Load the bitmap
        SelectObject(hdc_x, hBitmap); //Put the bitmap into the hdc_x
        
        // RECT rect;
        // GetWindowRect(m_hwnd, &rect);
        
        BitBlt(hdc, 0, 0, 1200, 800, hdc_x, 0, 0, SRCCOPY); //Draw it.
        
        HFONT hFont = CreateFont(48, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, L"Roboto Th"); //Create the font. (I'm using Roboto Thin.)
        DeleteDC(hdc_x); //Delete the HDC containing the bitmap.
        SelectObject(hdc, hFont);
        
        SetTextColor(hdc, RGB(255, 255, 255)); //White text.
        SetBkMode(hdc, TRANSPARENT); //Transparent background.
        
        TextOut(hdc, 0, 0, L"Team Stream presents....", strlen("We love nice pictures.")); //Print it!
        
        ReleaseDC(m_hwnd, hdc);
        ::EndPaint(m_hwnd, &ps);
    }




//     TextOut()
    
//     std::wstring introText = L"    _____ _____    _    __  __    ____ _____ ____  _____    _    __  __     \n   |_   _| ____|  / \\  |  \\/  |  / ___|_   _|  _ \\| ____|  / \\  |  \\/  |    \n     | | |  _|   / _ \\ | |\\/| |  \\___ \\ | | | |_) |  _|   / _ \\ | |\\/| |    \n     | | | |___ / ___ \\| |  | |   ___) || | |  _ <| |___ / ___ \\| |  | |    \n     |_| |_____/_/   \\_\\_|  |_|  |____/ |_| |_| \\_\\_____/_/   \\_\\_|  |_|    \n                                                 _                          \n                  _ __  _ __ ___  ___  ___ _ __ | |_ ___                    \n                 | '_ \\| '__/ _ \\/ __|/ _ \\ '_ \\| __/ __|                   \n                 | |_) | | |  __/\\__ \\  __/ | | | |_\\__ \\_ _ _              \n                 | .__/|_|  \\___||___/\\___|_| |_|\\__|___(_|_|_)             \n                 |_|                                                        ";

// // "    _____ _____    _    __  __    ____ _____ ____  _____    _    __  __     \n
// //    |_   _| ____|  / \  |  \/  |  / ___|_   _|  _ \| ____|  / \  |  \/  |    \n
// //      | | |  _|   / _ \ | |\/| |  \___ \ | | | |_) |  _|   / _ \ | |\/| |    \n
// //      | | | |___ / ___ \| |  | |   ___) || | |  _ <| |___ / ___ \| |  | |    \n
// //      |_| |_____/_/   \_\_|  |_|  |____/ |_| |_| \_\_____/_/   \_\_|  |_|    \n
// //                                                  _                          \n
// //                   _ __  _ __ ___  ___  ___ _ __ | |_ ___                    \n
// //                  | '_ \| '__/ _ \/ __|/ _ \ '_ \| __/ __|                   \n
// //                  | |_) | | |  __/\__ \  __/ | | | |_\__ \_ _ _              \n
// //                  | .__/|_|  \___||___/\___|_| |_|\__|___(_|_|_)             \n
// //                  |_|                                                        "

//     SendMessage(m_hwnd, WM_SETFONT, WPARAM(myFont), TRUE);
//     CreateWindow(L"Static", (LPCWSTR)introText.c_str(), WS_VISIBLE | WS_CHILD, 0, 0, 1200, 800, m_hwnd, NULL, NULL, NULL);
}