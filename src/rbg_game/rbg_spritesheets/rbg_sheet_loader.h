#ifndef RBG_SPRITESHEET_LOADER_H
#define RBG_SPRITESHEET_LOADER_H

#include "../rbg_game_context.h"
#include "raylib.h"

void rbg_init_sprite_sheet_loader(RbgGameContext* game_ctx);
void rbg_load_sprite_sheets(RbgGameContext* game_ctx, const char *csv_path);
void rbg_unload_sprite_sheets(RbgGameContext* game_ctx);
SpriteSheet* rbg_get_sprite_sheet_by_name(RbgGameContext* game_ctx, const char *spritesheet_name);

#endif
