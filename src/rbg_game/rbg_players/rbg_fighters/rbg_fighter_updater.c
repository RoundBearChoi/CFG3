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

// X-macro magic: builds the table automatically
rbg_fighter_update_func rbg_fighter_update_functions[NUM_FIGHTER_STATES] = {
#define X(state) [state] = update_##state,
    RBG_FIGHTER_STATES(X)
#undef X
};

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
