#include<windows.h>
#include<chrono>
#include<thread>
#include "console.h"

void ClearScreen() {
  HANDLE                     hStdOut;
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  DWORD                      count;
  DWORD                      cellCount;
  COORD                      homeCoords = { 0, 0 };

  hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
  if (hStdOut == INVALID_HANDLE_VALUE) return;

  /* Get the number of cells in the current buffer */
  if (!GetConsoleScreenBufferInfo( hStdOut, &csbi )) return;
  cellCount = csbi.dwSize.X *csbi.dwSize.Y;

  /* Fill the entire buffer with spaces */
  if (!FillConsoleOutputCharacter(
    hStdOut,
    (TCHAR) ' ',
    cellCount,
    homeCoords,
    &count
    )) return;

  /* Fill the entire buffer with the current colors and attributes */
  if (!FillConsoleOutputAttribute(
    hStdOut,
    csbi.wAttributes,
    cellCount,
    homeCoords,
    &count
    )) return;

  /* Move the cursor home */
  SetConsoleCursorPosition( hStdOut, homeCoords );
}

void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

void initScreen() {
    /**
     * @brief here the window is set up for the game - size of window is set and resizing functionalities removed
     * 
     */
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);   // retrives height of monitor
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);    // retrieves width of monitor

    int posX = (screenWidth - 1200) / 2;    // calculates offset from edge of screen to corner the game window
    int posY = (screenHeight - 800) / 2;    // calculates offset from top of screen to corner of the window
    HWND window = GetConsoleWindow();   // retrieves window handle of console

    MoveWindow(window, posX, posY, 1202, 795, TRUE);    // moves window on screen - 194 characters wide by 62 tall
    SetWindowLong(window, GWL_STYLE,    // selects current window and characteristic to be updated (window style)
                  GetWindowLong(window, GWL_STYLE)  // returns current style of window
                  & ~WS_MAXIMIZEBOX     // inactive maximise box
                  & ~WS_SIZEBOX);       // removes resizing box around window
}

void removeScroll() {
    /**
     * @brief scrolling is deactivated by setting maximum buffer size of console screen to same as window size
     * 
     */

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);   // retrieves handle of main monitor
    
    CONSOLE_SCREEN_BUFFER_INFO screenBuffer;    // creates new structure to store the buffer information
    GetConsoleScreenBufferInfo(hStdOut, &screenBuffer); // retrieves buffer info of screen and saves into screenBuffer variable

    screenBuffer.dwSize.X = 1200; // sets max width of console to current window width
    screenBuffer.dwSize.Y = 800; // sets max height of console to current window height
    SetConsoleScreenBufferSize(hStdOut, screenBuffer.dwSize);   // updates console buffer with new values
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    // Sleep(0.5);
    HWND window = GetConsoleWindow();       // retrieves window handle of console
    ShowScrollBar(window, SB_BOTH, FALSE);  // removes the scroll bar
}

void setup() {
    
    SetConsoleTitle("The Dungeon Chronicles");
    initScreen();
    removeScroll();
    ShowConsoleCursor(false);

}
