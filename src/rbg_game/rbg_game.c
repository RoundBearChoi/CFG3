#include "rbg_game.h"
#include "rbg_input/rbg_update_input.h"
#include "rbg_scenes/rbg_scenes.h"
#include "rbg_render_debug/rbg_render_debug.h"
#include "raylib.h"

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
	}

    // Fixed timestep setup
    static double accumulator = 0.0;
    const double fixed_dt = 1.0 / 60.0;

    // Get elapsed time since last frame
    double frame_time = GetFrameTime();
    accumulator += frame_time;

    // Input runs every rendered frame (variable timestep)
    rbg_update_input();

    // Fixed timestep loop — game logic runs at 60 fps
    while (accumulator >= fixed_dt)
    {
        rbg_update_scenes();
        accumulator -= fixed_dt;
    }

    // Debug rendering runs every frame (after logic)
    rbg_render_debug();
}
