#ifndef RBG_PLAYER_BOX_H
#define RBG_PLAYER_BOX_H

#include <stdbool.h>

#include "raylib.h"

typedef struct
{
	int player_index;
	bool is_colliding_with_other_player;

	float width;
	float height;
	float offset_x;
	float offset_y;

	// Collision result stored after detection (to avoid recalculating in resolve)
	float overlap_x;   // Positive value = how much the boxes overlap horizontally

} rbg_player_col_box;

extern rbg_player_col_box rbg_player_1_box;
extern rbg_player_col_box rbg_player_2_box;

void rbg_init_player_boxes();
void rbg_reset_box(rbg_player_col_box* box);
void rbg_update_player_boxes();
void rbg_check_collision(void);
rbg_player_col_box* rbg_get_player_box(int playerIndex);

#endif