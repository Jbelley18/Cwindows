#include <windows.h>
#include <stdio.h>
#include "window_enum.h"
#include "layout_tile.h"
#include "tray_icon.h"
#include "config.h"

#define HOTKEY_ENUM 1
#define HOTKEY_TILE 2


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    HWND trayWindow = create_tray_window(hInstance);
    setup_tray_icon(trayWindow);
    
    load_config("config.toml");

    RegisterHotKey(NULL, HOTKEY_ENUM, hotkeys.info.modifiers, hotkeys.info.key);
    RegisterHotKey(NULL, HOTKEY_TILE, hotkeys.tile.modifiers, hotkeys.tile.key);


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
