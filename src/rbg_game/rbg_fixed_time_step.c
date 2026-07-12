#include "rbg_fixed_time_step.h"
#include "raylib.h"

void rbg_init_fixed_time_step(RbgGameContext* game_ctx)
{
    if (!game_ctx) return;

    game_ctx->accumulator   = 0.0;
    game_ctx->previous_time = 0.0;

	game_ctx->fps_count = 0;
	game_ctx->fps_display = 0;
	game_ctx->fps_timer = 0.0;

    if (game_ctx->target_fps == 128)
    {
        game_ctx->fixed_dt = 1.0 / 128.0;
    }
    else if (game_ctx->target_fps == 60)
    {
        game_ctx->fixed_dt = 1.0 / 60.0;
    }
    else
    {
        game_ctx->fixed_dt = 1.0 / 60.0; // fallback
    }
}

void rbg_accumulate_fixed_time_step(RbgGameContext* game_ctx)
{
    if (!game_ctx) return;

    if (game_ctx->previous_time == 0.0)
    {
        game_ctx->previous_time = GetTime();
    }

    double current_time = GetTime();
    game_ctx->frame_time = current_time - game_ctx->previous_time;
    game_ctx->previous_time = current_time;
    game_ctx->accumulator += game_ctx->frame_time;

	// for fps display
	game_ctx->fps_timer += game_ctx->frame_time;
	game_ctx->fps_count++;

	if (game_ctx->fps_timer >= 1.0)
	{
		game_ctx->fps_display = game_ctx->fps_count;
		game_ctx->fps_count = 0;
		game_ctx->fps_timer = 0.0;
	}
}

bool rbg_run_fixed_time_step(RbgGameContext* game_ctx)
{
    if (!game_ctx) return false;

    if (game_ctx->accumulator >= game_ctx->fixed_dt)
    {
        game_ctx->accumulator -= game_ctx->fixed_dt;
        return true;
    }
    return false;
}
