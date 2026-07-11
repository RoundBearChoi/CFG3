#ifndef RBG_RENDER_DEBUG_H
#define RBG_RENDER_DEBUG_H

#include "../rbg_game_context.h"

void rbg_render_debug(RbgGameContext* game_ctx);
void rbg_draw_x_on_player_pos(RbgGameContext* game_ctx);
void rbg_draw_player_boxes(RbgGameContext* game_ctx, int playerIndex);

#endif
