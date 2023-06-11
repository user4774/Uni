/**
 * @file window.cpp
 * @author James Askew
 * @brief 
 * @version 0.1
 * @date 2021-03-07
 * 
 */

#include "window.h"
#include "appWindow.h"
#include<windows.h>
#include<string>
#include<filesystem>

Window* window = nullptr;

Window::Window() {

};

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

    switch(uMsg) {
        case WM_CREATE:
            // event called out when window is first created
            window->onCreate();
            break;

        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            HDC hdc_x = CreateCompatibleDC(NULL);
            // std::filesystem::path p = "intro_background.bmp";
            // std::string path = std::filesystem::absolute(p);

            HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, L"intro_background.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
            SelectObject(hdc_x, hBitmap);
            
            RECT rect;
            GetWindowRect(hwnd, &rect);
            
            BitBlt(hdc, 0, 0, 1200, 800, hdc_x, 0, 0, SRCCOPY);
            
            HFONT hFont = CreateFont(48, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, L"Roboto Th");
            DeleteDC(hdc_x);
            SelectObject(hdc, hFont);
            
            SetTextColor(hdc, RGB(0, 0, 0));
            SetBkMode(hdc, TRANSPARENT);
            
            std::wstring introductionText = L"Introducing...";

            TextOut(hdc, 0, 0, (LPCWSTR)introductionText.c_str(), strlen("Introducing..."));
            
            ReleaseDC(hwnd, hdc);
            EndPaint(hwnd, &ps);
        }
            // window.OnPaint();
            break;

        case WM_DESTROY:
            //event called when window will be destroyed
            window->onDestroy();
            ::PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

bool Window::init() {
    // create the window in which the game is played

    WNDCLASSEX wc;

    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = 0;
    wc.lpfnWndProc = WindowProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = NULL;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.lpszMenuName = L"";
    wc.lpszClassName = L"Window";
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    if (!::RegisterClassEx(&wc)) {
        return false;
    }

    if(!window) {
        window = this;
    }

    m_hwnd = ::CreateWindowEx(
        0,
        L"Window",
        L"Team Stream - Fantasy RPG",
        // WS_OVERLAPPEDWINDOW,
        WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME,

        CW_USEDEFAULT, CW_USEDEFAULT, 1200, 800,

        NULL,
        NULL,
        NULL,
        NULL
        );

    // if the window creation fails, return false
    if (!m_hwnd) {
        return false;
    }

    // make window visible and paint contents
    ::ShowWindow(m_hwnd, SW_SHOW);
    ::UpdateWindow(m_hwnd);

    gameRunning = true;

    return true;
};

bool Window::release() {
    // destroy the window

    if(!::DestroyWindow(m_hwnd)) {
        return false;
    }
    return true;
};

void Window::onCreate() {
}

void Window::onUpdate() {
}

void Window::onDestroy() {
    gameRunning = false;
}

bool Window::isRunning() {
    return gameRunning;
}

bool Window::broadcast() {

    MSG msg;

    while(::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    window->onUpdate();

    Sleep(0);

    return true;
}

Window::~Window() {

};
