#ifndef RBG_FIXED_TIME_STEP_H
#define RBG_FIXED_TIME_STEP_H

#include "rbg_game_context.h"
#include <stdbool.h>

void rbg_init_fixed_time_step(RbgGameContext* ctx);
void rbg_accumulate_fixed_time_step(RbgGameContext* ctx);
bool rbg_run_fixed_time_step(RbgGameContext* ctx);

#endif
