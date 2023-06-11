/**
 * @file console.cpp
 * @author James Askew
 * @brief 
 * @version 0.1
 * @date 2021-03-06
 * 
 * http://www.winprog.org/tutorial/start.html
 * https://www.youtube.com/watch?v=8GCvZs55mEM&list=PLWzp0Bbyy_3i750dsUj7yq4JrPOIUR_NK&index=2
 * https://www.youtube.com/watch?v=ssGka-bSTvQ&list=PLv8DnRaQOs5-ST_VDqgbbMRtzMtpK36Hy&index=2
 * add -municode suffix to linker command
 */

#ifndef _UNICODE
#define _UNICODE
#endif 

#ifndef UNICODE
#define UNICODE
#endif

#define FILE_MENU_NEW 11    // first digit refers to menu bar position of menu option, second refers to sub-menu option 
#define FILE_MENU_OPEN 12
#define FILE_MENU_SAVE 13
#define FILE_MENU_EXIT 14
#define EDIT_MENU_SETTINGS 31
#define EDIT_MENU_CHANGE_TITLE 32

#include <windows.h>
#include <iostream>
#include "placeholder_player.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

void addMenu(HWND hwnd);

void addControls(HWND hwnd);

HMENU hMenuBar;
HWND hEdit;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {

    const wchar_t CLASS_NAME[]  = L"StandardWindow";
    
    WNDCLASS wc = { };

    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    
    if (!RegisterClass(&wc)) {
        return 0;
    };

    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        L"Team Stream - Fantasy RPG",
        WS_OVERLAPPEDWINDOW,

        CW_USEDEFAULT, CW_USEDEFAULT, 1200, 800,

        NULL,
        NULL,
        hInstance,
        NULL
        );

    if (hwnd == NULL) {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    
    switch (uMsg) {

        case WM_CREATE:
            addMenu(hwnd);
            addControls(hwnd);
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
            break;

        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        case WM_COMMAND:
            switch(wParam) {
                case FILE_MENU_EXIT:
                    DestroyWindow(hwnd);
                    break;

                case FILE_MENU_NEW:
                    MessageBeep(MB_ICONINFORMATION);
                    break;

                case EDIT_MENU_CHANGE_TITLE:
                    wchar_t text[100];
                    GetWindowTextW(hEdit, text, 100);
                    SetWindowTextW(hwnd, text);
            }
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

void addMenu(HWND hwnd) {
    
    hMenuBar = CreateMenu();
    HMENU hFileMenu = CreateMenu();
    HMENU hLoadMenu = CreateMenu();
    HMENU hEditMenu = CreateMenu();


    AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hFileMenu, L"File");
    AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hEditMenu, L"Edit");
    AppendMenu(hMenuBar, MF_STRING, 0, L"Help");

    AppendMenu(hFileMenu, MF_STRING, 0, L"Pause");
    AppendMenu(hFileMenu, MF_SEPARATOR, 0, NULL);
    AppendMenu(hFileMenu, MF_STRING, FILE_MENU_NEW, L"New Game");
    AppendMenu(hFileMenu, MF_SEPARATOR, 0, NULL);
    AppendMenu(hFileMenu, MF_POPUP, FILE_MENU_OPEN, L"Open Saved Game");
    AppendMenu(hFileMenu, MF_POPUP, (UINT_PTR)hLoadMenu, L"Load Recent Game");
    AppendMenu(hFileMenu, MF_STRING, FILE_MENU_SAVE, L"Save");
    AppendMenu(hFileMenu, MF_SEPARATOR, 0, NULL);
    AppendMenu(hFileMenu, MF_STRING, FILE_MENU_EXIT, L"Quit");

    AppendMenu(hLoadMenu, MF_STRING, 0, L"Example Save 1");
    AppendMenu(hLoadMenu, MF_STRING, 0, L"Example Save 2");
    AppendMenu(hLoadMenu, MF_STRING, 0, L"Example Save 3");

    AppendMenu(hEditMenu, MF_STRING, EDIT_MENU_SETTINGS, L"Settings");
    AppendMenu(hEditMenu, MF_STRING, EDIT_MENU_CHANGE_TITLE, L"Change Title");

    SetMenu(hwnd, hMenuBar);
}

void addControls(HWND hwnd) {

    MockPlayer player;
    std::wstring hp = std::to_wstring(player.hp).c_str();
    std::wstring xp = std::to_wstring(player.xp).c_str();
    std::wstring levelUpXp = std::to_wstring(player.levelxp).c_str();
    std::wstring playerStatus = L"Health " + hp + L"\n  XP " + xp + L"/" + levelUpXp;

    // CreateWindowW(L"static", (LPCWSTR)playerStatus.c_str(), WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE, 0, 0, 1200, 18, hwnd, NULL, NULL, NULL);
    hEdit = CreateWindowW(L"edit", L"100", WS_VISIBLE | WS_CHILD, 0, 300, 1500, 300, hwnd, NULL, NULL, NULL);

}

/*
 * print map
 * press key
 * update map
 * print map
 */
