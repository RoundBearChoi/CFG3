#ifndef RBG_PLAYER_BOX_H
#define RBG_PLAYER_BOX_H

#include "../rbg_game_context.h"
#include <stdbool.h>
#include "raylib.h"

void rbg_init_player_boxes(RbgGameContext* game_ctx);
void rbg_reset_box(rbg_player_col_box* box);
void rbg_update_player_boxes(RbgGameContext* game_ctx);
void rbg_check_collision(RbgGameContext* game_ctx);
rbg_player_col_box* rbg_get_player_box(RbgGameContext* game_ctx, int playerIndex);

#endif
