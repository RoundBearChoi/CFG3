#include "rbg_fixed_time_step.h"
#include "raylib.h"

void rbg_init_fixed_time_step(RbgGameContext* ctx)
{
    if (!ctx) return;

    ctx->accumulator   = 0.0;
    ctx->previous_time = 0.0;

    if (global_rbg_target_fps == 128)
    {
        ctx->fixed_dt = 1.0 / 128.0;
    }
    else if (global_rbg_target_fps == 60)
    {
        ctx->fixed_dt = 1.0 / 60.0;
    }
    else
    {
        ctx->fixed_dt = 1.0 / 60.0; // fallback
    }
}

void rbg_accumulate_fixed_time_step(RbgGameContext* ctx)
{
    if (!ctx) return;

    if (ctx->previous_time == 0.0)
    {
        ctx->previous_time = GetTime();
    }

    double current_time = GetTime();
    global_rbg_frame_time = current_time - ctx->previous_time;
    ctx->previous_time = current_time;
    ctx->accumulator += global_rbg_frame_time;
}

bool rbg_run_fixed_time_step(RbgGameContext* ctx)
{
    if (!ctx) return false;

    if (ctx->accumulator >= ctx->fixed_dt)
    {
        ctx->accumulator -= ctx->fixed_dt;
        return true;
    }
    return false;
}
