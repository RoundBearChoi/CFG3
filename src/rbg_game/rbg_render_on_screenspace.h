#ifndef RBG_RENDER_ON_SCREENSPACE_H
#define RBG_RENDER_ON_SCREENSPACE_H

#include "rbg_game_context.h"
#include "raylib.h"

void rbg_render_on_screenspace(RbgGameContext* game_ctx);
void rbg_draw_scaled_text(const char* text, Vector2 pos, float fontSize, float font_spacing, Color color);

#endif
