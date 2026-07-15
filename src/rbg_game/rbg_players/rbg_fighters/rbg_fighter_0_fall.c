#include "rbg_fighter_0_fall.h"
#include "../../rbg_sprite_sheets/rbg_sheet_animators.h"

void update_fighter_0_fall(RbgGameContext* game_ctx, rbg_player* player)
{
	if (new_state_detected(player))
	{
		rbg_change_player_animation(game_ctx, player->player_index, "fighter_0_fall");
	}

	player->position.y += 3.0f;

	// temp..
	// If we hit or passed ground (y=0), clamp position and transition back to idle.
	// Idle's new_state_detected on next frame will start the idle animation.
	if (player->position.y >= 0.0f)
	{
		player->position.y = 0.0f;
		player->fighter_curr_state = fighter_0_idle;
		return;
	}
}
