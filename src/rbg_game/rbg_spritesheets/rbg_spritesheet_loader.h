#ifndef RBG_SPRITESHEET_LOADER_H
#define RBG_SPRITESHEET_LOADER_H

#include "raylib.h"

typedef struct {
    char *fighter_type;
    char *spritesheet_filename;
    int total_x;
    int total_y;
    int total_images;
    float render_scale;
    int play_delay;

    Texture2D texture;      // loaded by Raylib
    int frame_width;        // pre-computed: texture.width / total_x
    int frame_height;       // pre-computed: texture.height / total_y
} Spritesheet;

extern Spritesheet *spritesheets;
extern int spritesheet_count;

void LoadSpritesheets(const char *csv_path);
void UnloadSpritesheets(void);
Spritesheet* GetSpritesheet(const char *fighter_type);

#endif
