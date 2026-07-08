#include "rbg_fixed_time_step.h"
#include "raylib.h"

/*
    === static ===
    storage duration — variable lives for entire lifetime of program (same as a normal global)
    internal linkage — variable is private to this file only, no other .c  can access _accumulator directly, even if they include the header
    this is the key benefit
*/

static double _accumulator = 0.0;
static double _previous_time = 0.0;
static double _fixed_dt = 1.0 / 128.0;

void rbg_init_fixed_time_step(void)
{
    _accumulator = 0.0;
    _previous_time = 0.0;

	if (global_rbg_target_fps == 128)
	{
		_fixed_dt = 1.0 / 128.0;
	}
	else if (global_rbg_target_fps == 60)
	{
		_fixed_dt = 1.0 / 60.0;
	}
}

void rbg_accumulate_fixed_time_step(void)
{
    if (_previous_time == 0.0)
    {
        _previous_time = GetTime();
    }

    double current_time = GetTime();
    global_rbg_frame_time = current_time - _previous_time;
    _previous_time = current_time;
    _accumulator += global_rbg_frame_time;
}

bool rbg_run_fixed_time_step(void)
{
    if (_accumulator >= _fixed_dt)
    {
        _accumulator -= _fixed_dt;
        return true;
    }
    return false;
}
