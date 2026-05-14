#include "rbg_fighter_0_walk.h"
#include <stdio.h>

void update_fighter_0_walk(rbg_player* player)
{
	if (new_state_detected(player))
	{
		printf("player %d switched to walk forward state\n", player->player_index);
	}
}
