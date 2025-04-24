#ifndef TRAY_ICON_H
#define TRAY_ICON_H

#include <windows.h>

#define ID_TRAY_EXIT 1001
#define WM_TRAYICON (WM_USER + 1)

HWND create_tray_window(HINSTANCE hInstance);
void setup_tray_icon(HWND hwnd);
void cleanup_tray_icon(void);

#endif
