#include "rbg_fixed_time_step.h"
#include "raylib.h"

static double accumulator = 0.0;
static double previous_time = 0.0;
static double fixed_dt = 1.0 / 128.0;

void rbg_init_fixed_time_step(void)
{
    accumulator = 0.0;
    previous_time = 0.0;

	if (global_rbg_target_fps == 128)
	{
		fixed_dt = 1.0 / 128.0;
	}
	else if (global_rbg_target_fps == 60)
	{
		fixed_dt = 1.0 / 60.0;
	}
}

void rbg_accumulate_fixed_time_step(void)
{
    if (previous_time == 0.0)
    {
        previous_time = GetTime();
    }

    double current_time = GetTime();
    global_rbg_frame_time = current_time - previous_time;
    previous_time = current_time;
    accumulator += global_rbg_frame_time;
}

bool rbg_run_fixed_time_step(void)
{
    if (accumulator >= fixed_dt)
    {
        accumulator -= fixed_dt;
        return true;
    }
    return false;
}
