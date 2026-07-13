#ifndef RBG_PLAYER_CONTEXT_H
#define RBG_PLAYER_CONTEXT_H

#include "raylib.h"

typedef enum rbg_fighter_state {
	fighter_0_none,
	fighter_0_idle,
    fighter_0_walk,
    fighter_0_jump,
    fighter_0_fall,
    NUM_FIGHTER_STATES,
} rbg_fighter_state;

typedef struct rbg_player {
	int player_index;
    Vector2 position;
    bool is_facing_right_side;
	rbg_fighter_state fighter_curr_state;
	rbg_fighter_state fighter_prev_state;
} rbg_player;

typedef struct rbg_player_col_box {
	int player_index;
	bool is_colliding_with_other_player;

	float width;
	float height;
	float offset_x;
	float offset_y;

	// Collision result stored after detection (to avoid recalculating in resolve)
	float overlap_x;   // Positive value = how much the boxes overlap horizontally

} rbg_player_col_box;

#endif
