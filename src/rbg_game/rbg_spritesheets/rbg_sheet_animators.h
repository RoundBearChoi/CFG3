#ifndef RBG_SHEET_ANIMATORS_H
#define RBG_SHEET_ANIMATORS_H

#include "../rbg_game_context.h"
#include "rbg_sheet_loader.h"
#include "raylib.h"

void rbg_init_sheet_animators(RbgGameContext* game_ctx);
void rbg_update_sheet_animators(RbgGameContext* game_ctx);
void rbg_change_player_animation(RbgGameContext* game_ctx, int playerIndex, const char* sheet_name);
sprite_sheet_animator* rbg_get_player_sheet_animator(RbgGameContext* game_ctx, int playerIndex);
void rbg_init_animator(sprite_sheet_animator* ani, const char* spritesheet_name, rbg_render_pivot pivot);
void rbg_update_animator(sprite_sheet_animator* ani); // Advance animation (call every frame)
void rbg_draw_sprite_animation(const sprite_sheet_animator* ani, Vector2 position, float extra_scale, Color tint);
void rbg_reset_animator(sprite_sheet_animator* ani);

#endif
