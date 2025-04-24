// layout_tile.c - Tiling logic for arranging windows horizontally

#include <windows.h>
#include <stdio.h>
#include "layout_tile.h"

void tile_windows(HWND* hwnds, int count) {
    if (count <= 0) return;

    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    int windowWidth = screenWidth / count;
    int windowHeight = screenHeight; // full height

    for (int i = 0; i < count; ++i) {
        int x = i * windowWidth;
        SetWindowPos(hwnds[i], NULL, x, 0, windowWidth, windowHeight, SWP_NOZORDER | SWP_SHOWWINDOW);
    }

    printf("Tiled %d windows across the screen\n", count);
}
