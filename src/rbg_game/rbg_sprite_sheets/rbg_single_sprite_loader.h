#ifndef RBG_SINGLE_SPRITE_LOADER_H
#define RBG_SINGLE_SPRITE_LOADER_H

#include "../rbg_game_context.h"
#include "raylib.h"

void rbg_load_single_sprites(RbgGameContext* game_ctx, const char *csv_path);
void rbg_unload_single_sprites(RbgGameContext* game_ctx);
single_sprite* rbg_get_single_sprite_by_name(RbgGameContext* game_ctx, const char *sprite_name);

#endif
