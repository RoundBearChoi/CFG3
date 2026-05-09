#ifndef RBG_FIXED_TIME_STEP_H
#define RBG_FIXED_TIME_STEP_H
#include <stdbool.h>

// exposed for convenience
extern double rbg_frame_time;

void rbg_init_fixed_time_step(void);
void rbg_accumulate_fixed_time_step(void);
bool rbg_run_fixed_time_step(void);

#endif
