#ifndef RBG_GAME_SETTINGS_H
#define RBG_GAME_SETTINGS_H

#include <stdbool.h>

typedef struct RBG_GameSettings {
    bool render_debug;
} RBG_GameSettings;

extern RBG_GameSettings rbg_game_settings;

void rbg_load_game_settings(const char* json_path);  // pass NULL to use default path

#endif
