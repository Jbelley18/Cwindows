#ifndef CONFIG_H
#define CONFIG_H

#include <windows.h>  // ✅ Needed for UINT

typedef struct {
    UINT modifiers;
    UINT key;
} Hotkey;

typedef struct {
    Hotkey tile;
    Hotkey info;
} HotkeyConfig;

extern HotkeyConfig hotkeys;

void load_config(const char* path);

#endif
