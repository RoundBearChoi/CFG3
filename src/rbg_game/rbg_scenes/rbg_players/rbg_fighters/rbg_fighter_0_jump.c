#include "rbg_fighter_0_jump.h"
#include "../../rbg_input/rbg_record_input_actions.h"
#include "../../../rbg_spritesheets/rbg_sheet_animators.h"
#include <stddef.h>

void update_fighter_0_jump(rbg_player* player)
{
	if (player == NULL) return;

	sprite_sheet_animator* ani = NULL;
	if (player->player_index == 1) ani = &sheet_animator_p1;
	else if (player->player_index == 2) ani = &sheet_animator_p2;

	// static timer for jump duration (initialized once, value persists; we reset on state entry)
	static int jump_timers[3] = {0, 0, 0};
	int idx = player->player_index;
	if (idx < 1 || idx > 2) return;

	if (new_state_detected(player))
	{
		rbg_change_player_animation(player->player_index, "fighter_0_jump");
		if (ani != NULL)
		{
			ani->loop = false;
			ani->is_playing = true;
		}
		jump_timers[idx] = 0;  // reset timer for this jump
	}

	jump_timers[idx]++;
	int t = jump_timers[idx];

	// start going up after 10 frames (matches first play_delay windup)
	// only while the one-shot animation is still playing
	if (t > 10 && ani && ani->is_playing)
	{
		player->position.y -= 3.0f;  // upward delta per fixed update; adjust for feel/height
	}

	// Animation plays exactly once (loop=false on entry).
	// After it finishes naturally, we do NOT switch back to idle.
	// State remains fighter_0_jump and the sprite freezes on the final frame.
	// (You can later add landing logic or manual state change from elsewhere.)
}
