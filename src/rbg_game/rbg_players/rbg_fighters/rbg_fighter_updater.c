#include "rbg_fighter_updater.h"
#include "../rbg_players.h"
#include "rbg_fighter_0_idle.h"
#include "rbg_fighter_0_walk.h"
#include "rbg_fighter_0_jump.h"
#include "rbg_fighter_0_fall.h"
#include <stdio.h>

rbg_fighter_update_func rbg_fighter_update_functions[NUM_FIGHTER_STATES];

void rbg_init_fighter_update_functions(void)
{
    rbg_fighter_update_functions[fighter_0_fall]          = update_fighter_0_fall;
    rbg_fighter_update_functions[fighter_0_idle]          = update_fighter_0_idle;
    rbg_fighter_update_functions[fighter_0_jump]          = update_fighter_0_jump;
    rbg_fighter_update_functions[fighter_0_walk]          = update_fighter_0_walk;
}

void rbg_update_fighter(RbgGameContext* game_ctx, int player_index)
{
	rbg_player* player = rbg_get_player(game_ctx, player_index);
    
	rbg_fighter_update_functions[player->fighter_curr_state](game_ctx, player);
}
