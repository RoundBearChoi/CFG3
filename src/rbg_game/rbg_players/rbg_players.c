#include "rbg_players.h"
#include "../rbg_game_context.h"
#include "../rbg_input/rbg_record_input_actions.h"
#include <stddef.h>
#include <stdio.h>

void rbg_init_players(RbgGameContext* game_ctx)
{
	printf("\n=== initializing players ===\n");

	game_ctx->player_1.player_index = 1;
	game_ctx->player_1.position = (Vector2){ 50.0f, 0.0f };
	game_ctx->player_1.is_facing_right_side = true;
	game_ctx->player_1.fighter_prev_state = fighter_0_none;
	game_ctx->player_1.fighter_curr_state = fighter_0_idle;

	game_ctx->player_2.player_index = 2;
	game_ctx->player_2.position = (Vector2){ 200.0f, 0.0f };
	game_ctx->player_2.is_facing_right_side = false;
	game_ctx->player_2.fighter_prev_state = fighter_0_none;
	game_ctx->player_2.fighter_curr_state = fighter_0_idle;
}

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

rbg_player* rbg_get_player(RbgGameContext* game_ctx, int playerIndex)
{
	if (playerIndex == 1)
	{
		return &game_ctx->player_1;
	}
	else if (playerIndex == 2)
	{
		return &game_ctx->player_2;
	}

	return NULL;
}
