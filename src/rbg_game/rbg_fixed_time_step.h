#ifndef RBG_FIXED_TIME_STEP_H
#define RBG_FIXED_TIME_STEP_H

#include "rbg_game.h"
#include <stdbool.h>

extern double global_rbg_frame_time;
extern const int global_rbg_target_fps;

void rbg_init_fixed_time_step(RbgGameContext* ctx);
void rbg_accumulate_fixed_time_step(RbgGameContext* ctx);
bool rbg_run_fixed_time_step(RbgGameContext* ctx);

#endif
