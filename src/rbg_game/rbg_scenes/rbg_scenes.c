#include "rbg_scenes.h"
#include "test_scene_1.h"
#include "test_scene_2.h"
#include "raylib.h"
#include <stddef.h>

static rbg_scene_type _current_scene = TEST_SCENE_2; // only used locally
rbg_scene_type rbg_next_scene = NONE; // accessed by other files to set next scene

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

void rbg_update_scenes(void)
{
    // safety: prevent crashes if somehow out of bounds
    if (_current_scene >= 0 && _current_scene < NUM_SCENES && scene_updates[_current_scene] != NULL)
	{
        scene_updates[_current_scene](); // run the scene update based on selected enum
    } 
	else
	{
        DrawText("ERROR: Invalid scene!", 200, 200, 30, RED);
    }

    // apply queued scene change at the end of the frame's update phase
    if (rbg_next_scene != NONE && rbg_next_scene != NUM_SCENES)
    {
        _current_scene = rbg_next_scene;
        rbg_next_scene = NONE;
        //TraceLog(LOG_INFO, "Scene switched to %d", (int)_current_scene);
    }
}

void rbg_render_scenes(void)
{
    // Mirror of update dispatch, but for rendering (called once per visual frame)
    if (_current_scene >= 0 && _current_scene < NUM_SCENES && scene_renders[_current_scene] != NULL)
	{
        scene_renders[_current_scene]();
    } 
	else
	{
        DrawText("ERROR: Invalid scene for render!", 200, 200, 30, RED);
    }
}
