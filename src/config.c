#include <windows.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "config.h"
#include "toml.h"

HotkeyConfig hotkeys;
LayoutType current_layout = LAYOUT_HORIZONTAL;  // default fallback

static UINT parse_modifiers(const char* str) {
    UINT mods = 0;
    if (strstr(str, "Ctrl"))  mods |= MOD_CONTROL;
    if (strstr(str, "Alt"))   mods |= MOD_ALT;
    if (strstr(str, "Shift")) mods |= MOD_SHIFT;
    if (strstr(str, "Win"))   mods |= MOD_WIN;
    return mods;
}

static UINT parse_key(const char* str) {
    const char* last = strrchr(str, '+');
    if (last) return toupper(last[1]);
    return toupper(str[0]);
}

static void load_hotkey(toml_table_t* table, const char* name, Hotkey* hk) {
    const char* raw_str = toml_raw_in(table, name);
    if (!raw_str) return;

    char* parsed = NULL;
    if (toml_rtos(raw_str, &parsed) == 0) {
        hk->modifiers = parse_modifiers(parsed);
        hk->key = parse_key(parsed);
        free(parsed);
    }
}

void load_config(const char* path) {
    FILE* f = fopen(path, "r");
    if (!f) {
        MessageBox(NULL, "Failed to open config.toml", "Error", MB_OK | MB_ICONERROR);
        exit(1);
    }

    char errbuf[200];
    toml_table_t* conf = toml_parse_file(f, errbuf, sizeof(errbuf));
    fclose(f);

    if (!conf) {
        MessageBox(NULL, errbuf, "TOML Parse Error", MB_OK | MB_ICONERROR);
        exit(1);
    }

    // Load hotkeys
    toml_table_t* hotkey_table = toml_table_in(conf, "hotkeys");
    if (hotkey_table) {
        load_hotkey(hotkey_table, "tile", &hotkeys.tile);
        load_hotkey(hotkey_table, "info", &hotkeys.info);
    }

    // Load layout type
    const char* raw_layout = toml_raw_in(conf, "layout");
    if (raw_layout) {
        char* parsed = NULL;
        if (toml_rtos(raw_layout, &parsed) == 0) {
            if (_stricmp(parsed, "vertical") == 0) {
                current_layout = LAYOUT_VERTICAL;
            } else {
                current_layout = LAYOUT_HORIZONTAL;
            }
            free(parsed);
        }
    }

    toml_free(conf);
}
