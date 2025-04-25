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

    if (!RegisterHotKey(NULL, HOTKEY_ENUM, hotkeys.info.modifiers, hotkeys.info.key)) {
        printf("Failed to register INFO hotkey. Error: %lu\n", GetLastError());
    } else {
        printf("Registered INFO hotkey (mod=0x%X, key=0x%X)\n", hotkeys.info.modifiers, hotkeys.info.key);
    }
    
    if (!RegisterHotKey(NULL, HOTKEY_TILE, hotkeys.tile.modifiers, hotkeys.tile.key)) {
        printf("Failed to register TILE hotkey. Error: %lu\n", GetLastError());
    } else {
        printf("Registered TILE hotkey (mod=0x%X, key=0x%X)\n", hotkeys.tile.modifiers, hotkeys.tile.key);
    }
    

    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);

        if (msg.message == WM_HOTKEY) {
            printf("Hotkey triggered: ID=%llu\n", (unsigned long long)msg.wParam);
            if (msg.wParam == HOTKEY_ENUM) {
                printf("Hotkey H pressed!\n");
                MessageBox(NULL, "Hotkey H Activated!", "Hotkey", MB_OK);
            } else if (msg.wParam == HOTKEY_TILE) {
                printf("Hotkey triggered: TILE (mod=0x%X, key=0x%X)\n", hotkeys.tile.modifiers, hotkeys.tile.key);
        
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
