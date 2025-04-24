// window_enum.c - Collects visible windows for layout tiling

#include <windows.h>
#include <stdio.h>
#include <string.h>
#include "window_enum.h"

#define MAX_TITLE_LENGTH 256

static HWND* hwndBuffer = NULL;
static int hwndCount = 0;
static int hwndMax = 0;

BOOL CALLBACK EnumWindowsCallback(HWND hwnd, LPARAM lParam) {
    char title[MAX_TITLE_LENGTH];

    if (IsWindowVisible(hwnd) &&
        GetWindowTextA(hwnd, title, sizeof(title)) &&
        title[0] != '\0') {

        if (hwndCount < hwndMax) {
            hwndBuffer[hwndCount++] = hwnd;
        }
    }

    return TRUE; // keep enumerating
}

int collect_visible_windows(HWND* buffer, int maxCount) {
    hwndBuffer = buffer;
    hwndCount = 0;
    hwndMax = maxCount;

    EnumWindows(EnumWindowsCallback, 0);
    return hwndCount;
}
