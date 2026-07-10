#ifndef RBG_PLAYER_BOX_H
#define RBG_PLAYER_BOX_H

#include "../rbg_game_context.h"
#include <stdbool.h>
#include "raylib.h"

extern rbg_player_col_box rbg_player_1_box;
extern rbg_player_col_box rbg_player_2_box;

void rbg_init_player_boxes();
void rbg_reset_box(rbg_player_col_box* box);
void rbg_update_player_boxes();
void rbg_check_collision(void);
rbg_player_col_box* rbg_get_player_box(int playerIndex);

#endif
