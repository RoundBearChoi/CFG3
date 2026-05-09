#include "rbg_game.h"
#include "rbg_input/rbg_update_input.h"
#include "rbg_scenes/rbg_scenes.h"
#include "rbg_render_debug/rbg_render_debug.h"
#include "rbg_fixed_update_count.h"
#include "rbg_fixed_time_step.h"
#include "raylib.h"

double rbg_frame_time = 0.0f;
int rbg_target_fps = 120;

static bool rbg_game_initialized = false;

void rbg_init_game()
{

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
    
    // fixed timestep loop — game logic runs at 120 fps
    while (rbg_run_fixed_time_step())
    {
        rbg_update_scenes();
        rbg_fixed_update_count();
        rbg_render_debug();
    }
}
