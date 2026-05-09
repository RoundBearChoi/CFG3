#include "rbg_fixed_update_count.h"
#include "raylib.h"

int rbg_fixed_updates = 0;
double rbg_accumulated_dt = 0.0;

static double prev_time = 0.0f;
static double curr_time = 0.0f;
static bool fixed_update_count_initialized = false;
static int fixed_updates = 0;

void rbg_init_fixed_update_count(void)
{
	prev_time = GetTime();
	curr_time = GetTime();
}

void rbg_fixed_update_count(void)
{
	if (fixed_update_count_initialized == false)
	{
		fixed_update_count_initialized = true;
		rbg_init_fixed_update_count();
	}

	if (rbg_accumulated_dt >= 1.0)
	{
		rbg_fixed_updates = fixed_updates;

		fixed_updates = 0;
		rbg_accumulated_dt = 0.0;
		prev_time = GetTime();
	}
	
	fixed_updates++;
	curr_time = GetTime();
	rbg_accumulated_dt = curr_time - prev_time;
}
