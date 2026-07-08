#include "rbg_game.h"
#include "rbg_game_settings.h"
#include "rbg_scenes/rbg_input/rbg_update_input.h"
#include "rbg_scenes/rbg_scenes.h"
#include "rbg_render_debug/rbg_render_debug.h"
#include "rbg_fixed_update_count.h"
#include "rbg_fixed_time_step.h"
#include "raylib.h"
#include <stddef.h>

double rbg_frame_time = 0.0f;
const int global_rbg_target_fps = 128; //the authoritative definition
Font press_start;

static bool rbg_game_initialized = false;

void rbg_init_game()
{
	rbg_load_game_settings(NULL);
}

void rbg_update_game(void)
{
	if (rbg_game_initialized == false)
	{
		rbg_game_initialized = true;
		rbg_init_game();
		rbg_init_fixed_time_step();
	}

    rbg_update_input();
    rbg_accumulate_fixed_time_step();
    
    // fixed timestep loop - multiple updates if behind (for determinism)
    while (rbg_run_fixed_time_step())
    {
        rbg_update_scenes();
        rbg_fixed_update_count();
    }
    
    // Render scenes once per frame (after fixed updates, inside camera in main.c)
	rbg_render_scenes();
	rbg_render_debug();
}
