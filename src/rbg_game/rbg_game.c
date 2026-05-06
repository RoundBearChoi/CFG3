#include "rbg_game.h"
#include "rbg_input/rbg_update_input.h"
#include "rbg_scenes/rbg_scenes.h"
#include "rbg_render_debug/rbg_render_debug.h"
#include "raylib.h"

void rbg_update_game(void)
{
    // Fixed timestep setup
    static double rbg_accumulator = 0.0;
    const double rbg_fixed_dt = 1.0 / 60.0;

    // Get elapsed time since last frame
    double rbg_frame_time = GetFrameTime();
    rbg_accumulator += rbg_frame_time;

    // Input runs every rendered frame (variable timestep)
    rbg_update_input();

    // Fixed timestep loop — game logic runs at 60 fps
    while (rbg_accumulator >= rbg_fixed_dt)
    {
        rbg_update_scenes();
        rbg_accumulator -= rbg_fixed_dt;
    }

    // Debug rendering runs every frame (after logic)
    rbg_render_debug();
}
