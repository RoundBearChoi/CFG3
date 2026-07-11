#include "rbg_scenes.h"
#include "test_scene_1.h"
#include "test_scene_2.h"
#include "raylib.h"
#include <stddef.h>

// Array of function pointers for updates - indexed by rbg_scene_type enum
static SceneUpdateFn scene_updates[NUM_SCENES] =
{
    update_test_scene_1,
    update_test_scene_2,
};

// Array of function pointers for renders - indexed by rbg_scene_type enum (mirrors the update pattern)
static SceneRenderFn scene_renders[NUM_SCENES] =
{
    render_test_scene_1,
    render_test_scene_2,
};

void rbg_init_scenes(RbgGameContext* ctx)
{
	ctx->current_scene = TEST_SCENE_2;
	ctx->next_scene = NONE;
}

void rbg_update_scenes(RbgGameContext* ctx)
{
    // safety: prevent crashes if somehow out of bounds
    if (ctx->current_scene >= 0 && ctx->current_scene < NUM_SCENES && scene_updates[ctx->current_scene] != NULL)
	{
        scene_updates[ctx->current_scene](ctx); // run the scene update based on selected enum
    } 
	else
	{
        DrawText("ERROR: Invalid scene!", 200, 200, 30, RED);
    }

    // apply queued scene change at the end of the frame's update phase
    if (ctx->next_scene != NONE && ctx->next_scene != NUM_SCENES)
    {
        ctx->current_scene = ctx->next_scene;
        ctx->next_scene = NONE;
        //TraceLog(LOG_INFO, "Scene switched to %d", (int)_current_scene);
    }
}

void rbg_render_scenes(RbgGameContext* ctx)
{
    // Mirror of update dispatch, but for rendering (called once per visual frame)
    if (ctx->current_scene >= 0 && ctx->current_scene < NUM_SCENES && scene_renders[ctx->current_scene] != NULL)
	{
        scene_renders[ctx->current_scene](ctx);
    } 
	else
	{
        DrawText("ERROR: Invalid scene for render!", 200, 200, 30, RED);
    }
}

void rbg_set_next_scene(RbgGameContext* ctx, rbg_scene_type next_scene)
{
	if (next_scene >= 0 && next_scene < NUM_SCENES)
	{
		ctx->next_scene = next_scene;
	}
}
