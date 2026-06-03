#include "rbg_scenes.h"
#include "test_scene_1.h"
#include "test_scene_2.h"
#include "raylib.h"
#include <stddef.h>

rbg_scene_type rbg_current_scene = TEST_SCENE_2;
rbg_scene_type rbg_next_scene = NONE;

// Array of function pointers - indexed by GameScene enum
static SceneUpdateFn scene_updates[NUM_SCENES] =
{
    update_test_scene_1,
    update_test_scene_2,
};

void rbg_update_scenes(void)
{
    // safety: prevent crashes if somehow out of bounds
    if (rbg_current_scene >= 0 && rbg_current_scene < NUM_SCENES && scene_updates[rbg_current_scene] != NULL)
	{
        scene_updates[rbg_current_scene](); // run the scene update based on selected enum
    } 
	else
	{
        DrawText("ERROR: Invalid scene!", 200, 200, 30, RED);
    }

    // apply queued scene change at the end of the frame
    if (rbg_next_scene != NONE && rbg_next_scene != NUM_SCENES)
    {
        rbg_current_scene = rbg_next_scene;
        rbg_next_scene = NONE;
        //TraceLog(LOG_INFO, "Scene switched to %d", (int)rbg_current_scene);
    }
}

void rbg_render_scenes(void)
{

}
