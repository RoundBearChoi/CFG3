#include "rbg_fighter_0_idle.h"
#include <stdio.h>

void update_fighter_0_idle(rbg_player* player)
{
	if (new_state_detected(player))
	{
		printf("player %d switched to idle state\n", player->player_index);
	}
}
