#ifndef RBG_FIXED_TIME_STEP_H
#define RBG_FIXED_TIME_STEP_H
#include <stdbool.h>

// Exposed for convenience
extern double rbg_frame_time;

// Public API
void rbg_init_fixed_time_step(void);
void rbg_accumulate_fixed_time_step(void);  // Call once per frame
bool rbg_run_fixed_time_step(void);         // Returns true if a fixed update should run this iteration

#endif
