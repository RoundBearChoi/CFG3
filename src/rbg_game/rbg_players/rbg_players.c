#include "rbg_players.h"
#include "../rbg_input/rbg_record_input_actions.h"
#include <stddef.h>
#include <stdio.h>

rbg_player rbg_player_1;
rbg_player rbg_player_2;

/*
// X-macro generated string literals array (must come after the header definition)
const char* const rbg_fighter_state_strings[NUM_FIGHTER_STATES] = {
#define X(state) [state] = #state,
    RBG_FIGHTER_STATES(X)
#undef X
};
*/

// specific to test scene 2
void rbg_init_players(void)
{
	printf("\n=== initializing players ===\n");

	rbg_player_1.player_index = 1;
	rbg_player_1.position = (Vector2){ 50.0f, 0.0f };
	rbg_player_1.is_facing_right_side = true;
	rbg_player_1.fighter_prev_state = fighter_uninitialized;
	rbg_player_1.fighter_curr_state = fighter_0_idle;

	rbg_player_2.player_index = 2;
	rbg_player_2.position = (Vector2){ 200.0f, 0.0f };
	rbg_player_2.is_facing_right_side = false;
	rbg_player_2.fighter_prev_state = fighter_uninitialized;
	rbg_player_2.fighter_curr_state = fighter_0_idle;
}

// specific to test scene 2
void rbg_update_players(void)
{
	// maybe update physics here
}

bool new_state_detected(rbg_player* player)
{
	if (player->fighter_prev_state != player->fighter_curr_state)
	{
		player->fighter_prev_state = player->fighter_curr_state; // new state can only be detected on the first update
		return true;
	}
	else
	{
		return false;
	}
}

rbg_player* rbg_get_player(int playerIndex)
{
	if (playerIndex == 1)
	{
		return &rbg_player_1;
	}
	else if (playerIndex == 2)
	{
		return &rbg_player_2;
	}

	return NULL;
}
