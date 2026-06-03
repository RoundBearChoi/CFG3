#include "rbg_fighter_0_fall.h"
#include "../../../rbg_spritesheets/rbg_sheet_animators.h"

void update_fighter_0_fall(rbg_player* player)
{
	if (new_state_detected(player))
	{
		// The jump animation was stopped in the jump state's exit logic.
		// We explicitly ensure is_playing is false here for robustness.
		// We intentionally do NOT switch to a 'fighter_0_fall' animation because no such
		// spritesheet exists yet in resources/fighters_spritesheet_list.csv.
		// The last frame of the jump animation will remain visible (frozen) while falling.
		sprite_sheet_animator* ani = rbg_get_player_sheet_animator(player->player_index);
		ani->is_playing = false;
	}

	// Fall by +3.0f in y every fixed update (positive y is down in Raylib coord system).
	// This mirrors the -3.0f ascent in jump state.
	player->position.y += 3.0f;

	// If we hit or passed ground (y=0), clamp position and transition back to idle.
	// Idle's new_state_detected on next frame will start the idle animation.
	if (player->position.y >= 0.0f)
	{
		player->position.y = 0.0f;
		player->fighter_curr_state = fighter_0_idle;
		return;
	}
}
