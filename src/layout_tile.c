#include <windows.h>
#include <stdio.h>
#include "layout_tile.h"
#include "config.h" // for current_layout

void tile_windows(HWND* hwnds, int count) {
    if (count <= 0) return;

    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    if (current_layout == LAYOUT_HORIZONTAL) {
        int windowWidth = screenWidth / count;

        for (int i = 0; i < count; ++i) {
            int x = i * windowWidth;
            SetWindowPos(hwnds[i], NULL, x, 0, windowWidth, screenHeight, SWP_NOZORDER | SWP_SHOWWINDOW);
        }

        printf("Tiled %d windows horizontally\n", count);

    } else if (current_layout == LAYOUT_VERTICAL) {
        int windowHeight = screenHeight / count;

        for (int i = 0; i < count; ++i) {
            int y = i * windowHeight;
            SetWindowPos(hwnds[i], NULL, 0, y, screenWidth, windowHeight, SWP_NOZORDER | SWP_SHOWWINDOW);
        }

        printf("Tiled %d windows vertically\n", count);
    }
}
