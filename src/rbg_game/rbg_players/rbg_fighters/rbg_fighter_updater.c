#include "rbg_fighter_updater.h"
#include "rbg_fighter_0_idle.h"
#include "rbg_fighter_0_walk.h"
#include "rbg_fighter_0_jump.h"
#include "rbg_fighter_0_fall.h"
#include <stdio.h>

// Handle the uninitialized state
static void update_fighter_uninitialized(RbgGameContext* game_ctx, rbg_player* player)
{
    printf("fighter_uninitialized state detected for player at %p\n", (void*)player);
}

rbg_fighter_update_func rbg_fighter_update_functions[NUM_FIGHTER_STATES];

void rbg_init_fighter_update_functions(void)
{
    rbg_fighter_update_functions[fighter_uninitialized]   = update_fighter_uninitialized;
    rbg_fighter_update_functions[fighter_0_idle]          = update_fighter_0_idle;
    rbg_fighter_update_functions[fighter_0_walk]          = update_fighter_0_walk;
    rbg_fighter_update_functions[fighter_0_jump]          = update_fighter_0_jump;
    rbg_fighter_update_functions[fighter_0_fall]          = update_fighter_0_fall;
}

void rbg_update_fighter(RbgGameContext* game_ctx, rbg_player* player)
{
    if (player == NULL)
    {
        printf("Error: rbg_update_fighter called with NULL player\n");
        return;
    }

    // Safety net for invalid/corrupted state
    if (player->fighter_curr_state < 0 || player->fighter_curr_state >= NUM_FIGHTER_STATES)
    {
        printf("Error: Invalid fighter state %d for player at %p\n", player->fighter_curr_state, (void*)player);
        player->fighter_curr_state = fighter_0_idle;
    }

    // Dispatch to the correct per-state update function
    rbg_fighter_update_functions[player->fighter_curr_state](game_ctx, player);
}
