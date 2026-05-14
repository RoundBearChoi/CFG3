#include "rbg_fighter_updater.h"
#include "rbg_fighter_0_idle.h"
#include "rbg_fighter_0_walk_forward.h"
#include <stdio.h>

// Handle the uninitialized state (defined here because it's not in its own file)
static void update_fighter_uninitialized(rbg_player* player)
{
    printf("Warning: fighter_uninitialized state detected for player at %p - forcing idle\n", (void*)player);
    player->fighter_curr_state = fighter_0_idle;
    player->fighter_prev_state = fighter_0_idle;
}

// X-macro magic: builds the table automatically
// update_fighter_uninitialized, update_fighter_0_idle, update_fighter_0_walk_forward, ...
rbg_fighter_update_func rbg_fighter_update_functions[NUM_FIGHTER_STATES] = {
#define X(state) [state] = update_##state,
    RBG_FIGHTER_STATES(X)
#undef X
};

void rbg_update_fighter(rbg_player* player)
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
    rbg_fighter_update_functions[player->fighter_curr_state](player);

    // Optional: you can also call a "late update" or record prev_state here if needed
    // player->fighter_prev_state = player->fighter_curr_state; // if you want to track changes
}
