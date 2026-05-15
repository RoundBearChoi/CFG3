#include "rbg_fighter_0_idle.h"
#include "../../rbg_input/rbg_record_input_actions.h"
#include "../../../rbg_spritesheets/rbg_sheet_animators.h"

void update_fighter_0_idle(rbg_player* player)
{
	if (new_state_detected(player))
	{
		rbg_change_player_animation(player->player_index, "fighter_0_idle");
	}

	if (rbg_input_action_is_pressed(rbg_get_move_right(player->player_index)))
	{
		player->is_facing_right_side = true;
		player->fighter_curr_state = fighter_0_walk;
		return;
	}
	
	if (rbg_input_action_is_pressed(rbg_get_move_left(player->player_index)))
	{
		player->is_facing_right_side = false;
		player->fighter_curr_state = fighter_0_walk;
		return;
	}

}
