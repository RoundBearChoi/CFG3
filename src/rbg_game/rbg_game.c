#include "rbg_game.h"
#include "rbg_input/rbg_update_input.h"
#include "rbg_scenes/rbg_scenes.h"
#include "rbg_render_debug/rbg_render_debug.h"
#include "rbg_fixed_update_count.h"
#include "raylib.h"

static bool rbg_game_initialized = false;

double rbg_frame_time = 0.0f;

void rbg_init_game()
{

}

void rbg_update_game(void)
{
	if (rbg_game_initialized == false)
	{
		rbg_game_initialized = true;
		rbg_init_game();
	}

    // Fixed timestep setup
    static double accumulator = 0.0;
    static double previous_time = 0.0;   // for manual delta time
    const double fixed_dt = 1.0 / 120.0;

    if (previous_time == 0.0)
    {
        previous_time = GetTime();
    }

    double current_time = GetTime();
    rbg_frame_time = current_time - previous_time;
    previous_time = current_time;
    accumulator += rbg_frame_time;
    
	rbg_update_input();

    // fixed timestep loop — game logic runs at 120 fps
    while (accumulator >= fixed_dt)
    {
        rbg_update_scenes();
        accumulator -= fixed_dt;
		
		rbg_fixed_update_count();
		rbg_render_debug();
    }
}
