#include <windows.h>
#include <stdio.h>

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam) {
    char title[256];
    if (IsWindowVisible(hwnd) && GetWindowTextA(hwnd, title, sizeof(title)) && title[0]) {
        printf("HWND: 0x%p - Title: %s\n", hwnd, title);
    }
    return TRUE;
}

int main() {
    // Register global hotkey: Ctrl + Alt + H
    if (!RegisterHotKey(NULL, 1, MOD_CONTROL | MOD_ALT, 0x48)) { // 0x48 = 'H'
        printf("Failed to register hotkey\n");
        return 1;
    }

    printf("Enumerating windows:\n");
    EnumWindows(EnumWindowsProc, 0);

    printf("\nListening for hotkey: Ctrl + Alt + H...\n");

    // Message loop to detect hotkey press
    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0)) {
        if (msg.message == WM_HOTKEY) {
            printf("Hotkey pressed!\n");
            MessageBox(NULL, "Hotkey Activated!", "Hotkey Event", MB_OK);
        }
    }

    // Unregister hotkey on exit (optional)
    UnregisterHotKey(NULL, 1);
    return 0;
}
