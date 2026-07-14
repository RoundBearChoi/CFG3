#include "rbg_game.h"
#include "rbg_game_settings.h"
#include "rbg_scenes/rbg_scenes.h"
#include "rbg_input/rbg_update_input.h"
#include "rbg_render_debug/rbg_render_debug.h"
#include "rbg_fixed_time_step.h"
#include "raylib.h"
#include <stddef.h>

Font global_font_press_start;

void rbg_init_game(void)
{
    rbg_load_game_settings(NULL);
}

void rbg_run_game(RbgGameContext* game_ctx)
{
    if (!game_ctx) return;

    if (game_ctx->game_initialized == false)
    {
        game_ctx->game_initialized = true;
        rbg_init_game();
		rbg_init_scenes(game_ctx);
    }

    rbg_update_input(game_ctx);
    rbg_accumulate_fixed_time_step(game_ctx);

    // fixed timestep loop - multiple updates if behind (for determinism)
    while (rbg_run_fixed_time_step(game_ctx))
    {
        rbg_update_scenes(game_ctx);
    }

    // Render scenes once per frame
    rbg_render_scenes(game_ctx);
    rbg_render_debug(game_ctx);
}
