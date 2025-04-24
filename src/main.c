#include <windows.h>
#include <stdio.h>
#include "window_enum.h"
#include "layout_tile.h"
#include "tray_icon.h"

#define HOTKEY_ENUM 1
#define HOTKEY_TILE 2


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    HWND trayWindow = create_tray_window(hInstance);
    setup_tray_icon(trayWindow);

    // Register hotkey: Ctrl + Alt + H (prints message box)
    if (!RegisterHotKey(NULL, HOTKEY_ENUM, MOD_CONTROL | MOD_ALT, 0x48)) {
        printf("Failed to register hotkey H\n");
        return 1;
    }

    // Register hotkey: Ctrl + Alt + Y (will trigger tiling later)
    if (!RegisterHotKey(NULL, HOTKEY_TILE, MOD_CONTROL | MOD_ALT, 0x59)) {
        printf("Failed to register hotkey Y\n");
        return 1;
    }

    printf("Listening for hotkeys...\n");

    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);

        if (msg.message == WM_HOTKEY) {
            if (msg.wParam == HOTKEY_ENUM) {
                printf("Hotkey H pressed!\n");
                MessageBox(NULL, "Hotkey H Activated!", "Hotkey", MB_OK);
            } else if (msg.wParam == HOTKEY_TILE) {
                HWND hwndList[32];
                int count = collect_visible_windows(hwndList, 32);
                tile_windows(hwndList, count);
            }
        }
    }

    UnregisterHotKey(NULL, HOTKEY_ENUM);
    UnregisterHotKey(NULL, HOTKEY_TILE);
    cleanup_tray_icon();
    return 0;
}
