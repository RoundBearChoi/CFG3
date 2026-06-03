#include "rbg_fighter_0_jump.h"
#include "../../rbg_input/rbg_record_input_actions.h"
#include "../../../rbg_spritesheets/rbg_sheet_animators.h"
#include "raylib.h"
#include <stddef.h>

void update_fighter_0_jump(rbg_player* player)
{
	// static timer for jump duration (initialized once, value persists; we reset on state entry)
	static int jump_timers[3] = {0, 0, 0};
	int idx = player->player_index;
	if (idx >= 3) return;
	
	sprite_sheet_animator* ani = NULL;
	ani = rbg_get_player_sheet_animator(player->player_index);

	if (new_state_detected(player))
	{
		rbg_change_player_animation(player->player_index, "fighter_0_jump");

		jump_timers[idx] = 0;  // reset timer for this jump
	}

	int t = jump_timers[idx];
	jump_timers[idx]++;


	// start going up after 10 frames (matches first play_delay windup)
	if (t >= 10 && t <= 10 * 6)
	{
		player->position.y -= 3.0f;  // upward delta per fixed update; adjust for feel/height
	}

	if (t >= 10 * 6)
	{
		ani->is_playing = false;
	}
}
