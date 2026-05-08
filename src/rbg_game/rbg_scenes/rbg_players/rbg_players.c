#include "rbg_players.h"
#include <stdio.h>

rbg_player rbg_player_1;
rbg_player rbg_player_2;

void rbg_init_players(void)
{
	printf("\n=== initializing players ===\n");

	rbg_player_1.position = (Vector2){ 200.0f, 0.0f };
	rbg_player_1.is_facing_right_side = true;
	
	rbg_player_2.position = (Vector2){ 600.0f, 0.0f };
	rbg_player_2.is_facing_right_side = false;
}

void rbg_update_players(void)
{

}
