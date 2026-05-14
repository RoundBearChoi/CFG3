#include "rbg_fighter_0_walk_forward.h"
#include <stdio.h>

void update_fighter_0_walk_forward(rbg_player* player)
{
	if (new_state_detected(player))
	{
		printf("player %d switched to walk forward state\n", player->player_index);
	}
}
