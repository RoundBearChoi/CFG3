#ifndef RBG_FIGHTER_UPDATER_H
#define RBG_FIGHTER_UPDATER_H

#include "../../rbg_game_context.h"
#include "../rbg_players.h"

// Function pointer type for state update
typedef void (*rbg_fighter_update_func)(RbgGameContext* game_ctx, rbg_player* player);

// Table of update functions (auto-generated via X-macro)
extern rbg_fighter_update_func rbg_fighter_update_functions[NUM_FIGHTER_STATES];

void rbg_init_fighter_update_functions(void);
void rbg_update_fighter(RbgGameContext* game_ctx, rbg_player* player);

#endif
