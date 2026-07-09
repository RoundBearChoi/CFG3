#include "rbg_scenes.h"
#include "test_scene_1.h"
#include "test_scene_2.h"
#include "raylib.h"
#include <stddef.h>

static rbg_scene_type _current_scene = TEST_SCENE_2;
static rbg_scene_type _next_scene = NONE;

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

void rbg_update_scenes(RbgGameContext* ctx)
{
    // safety: prevent crashes if somehow out of bounds
    if (_current_scene >= 0 && _current_scene < NUM_SCENES && scene_updates[_current_scene] != NULL)
	{
        scene_updates[_current_scene](ctx); // run the scene update based on selected enum
    } 
	else
	{
        DrawText("ERROR: Invalid scene!", 200, 200, 30, RED);
    }

    // apply queued scene change at the end of the frame's update phase
    if (_next_scene != NONE && _next_scene != NUM_SCENES)
    {
        _current_scene = _next_scene;
        _next_scene = NONE;
        //TraceLog(LOG_INFO, "Scene switched to %d", (int)_current_scene);
    }
}

void rbg_render_scenes(RbgGameContext* ctx)
{
    // Mirror of update dispatch, but for rendering (called once per visual frame)
    if (_current_scene >= 0 && _current_scene < NUM_SCENES && scene_renders[_current_scene] != NULL)
	{
        scene_renders[_current_scene](ctx);
    } 
	else
	{
        DrawText("ERROR: Invalid scene for render!", 200, 200, 30, RED);
    }
}

void rbg_set_next_scene(rbg_scene_type next_scene)
{
	if (next_scene >= 0 && next_scene < NUM_SCENES)
	{
		_next_scene = next_scene;
	}
}
