#ifndef RBG_SPRITESHEET_LOADER_H
#define RBG_SPRITESHEET_LOADER_H

#include "raylib.h"

typedef struct
{
    char *fighter_type;
    char *spritesheet_name;     // base name WITHOUT .png (automatically cleaned from CSV)
    int total_x;
    int total_y;
    int total_images;
    float render_scale;
    int play_delay;

    Texture2D texture;      // loaded by Raylib
    int frame_width;        // pre-computed: texture.width / total_x
    int frame_height;       // pre-computed: texture.height / total_y
} SpriteSheet;

extern SpriteSheet *spritesheets;
extern int spritesheet_count;

void rbg_load_sprite_sheets(const char *csv_path);
void rbg_unload_sprite_sheets(void);
SpriteSheet* GetSpriteSheetByName(const char *spritesheet_name);

#endif
