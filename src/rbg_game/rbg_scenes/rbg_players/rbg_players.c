#include "rbg_players.h"
#include "../rbg_input/rbg_record_input_actions.h"
#include <stdio.h>

rbg_player rbg_player_1;
rbg_player rbg_player_2;

// X-macro generated string literals array (must come after the header definition)
const char* const rbg_fighter_state_strings[NUM_FIGHTER_STATES] = {
#define X(state) [state] = #state,
    RBG_FIGHTER_STATES(X)
#undef X
};

// specific to test scene 2
void rbg_init_players(void)
{
	printf("\n=== initializing players ===\n");

	rbg_player_1.position = (Vector2){ 50.0f, 0.0f };
	rbg_player_1.is_facing_right_side = true;
	rbg_player_1.fighter_state = fighter_0_idle;

	rbg_player_2.position = (Vector2){ 200.0f, 0.0f };
	rbg_player_2.is_facing_right_side = false;
	rbg_player_2.fighter_state = fighter_0_idle;
}

// specific to test scene 2
void rbg_update_players(void)
{
	// maybe update physics here

	if (rbg_input_action_is_pressed(INPUT_P1_MOVE_LEFT))
	{
		rbg_player_1.position.x -= 2;
	}

	if (rbg_input_action_is_pressed(INPUT_P1_MOVE_RIGHT))
	{
		rbg_player_1.position.x += 2;
	}
}
