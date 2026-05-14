#ifndef RBG_FIGHTER_UPDATER_H
#define RBG_FIGHTER_UPDATER_H

#include "../rbg_players.h"

// Function pointer type for any state update
typedef void (*rbg_fighter_update_func)(rbg_player* player);

// Table of update functions (auto-generated via X-macro)
extern rbg_fighter_update_func rbg_fighter_update_functions[NUM_FIGHTER_STATES];

void rbg_update_fighter(rbg_player* player);

#endif
