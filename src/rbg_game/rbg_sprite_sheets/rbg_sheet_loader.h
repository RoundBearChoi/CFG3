#ifndef RBG_SPRITESHEET_LOADER_H
#define RBG_SPRITESHEET_LOADER_H

#include "../rbg_game_context.h"
#include "raylib.h"

void rbg_load_sprite_sheets(RbgGameContext* game_ctx, const char *csv_path);
void rbg_unload_sprite_sheets(RbgGameContext* game_ctx);
sprite_sheet* rbg_get_sprite_sheet_by_name(RbgGameContext* game_ctx, const char *sprite_sheet_name);

#endif
