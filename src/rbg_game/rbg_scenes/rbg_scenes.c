#include "rbg_scenes.h"
#include "test_scene_1.h"
#include "test_scene_2.h"
#include "raylib.h"
#include <stddef.h>

rbg_scene_type current_scene = TEST_SCENE_2;

// Array of function pointers - indexed by GameScene enum
static SceneUpdateFn scene_updates[NUM_SCENES] =
{
    update_test_scene_1,
    update_test_scene_2,
};

void rbg_update_scenes(void)
{
    // Safety: prevent crashes if somehow out of bounds
    if (current_scene >= 0 && current_scene < NUM_SCENES && scene_updates[current_scene] != NULL)
	{
        scene_updates[current_scene](); // run the scene update based on selected enum
    } 
	else
	{
        DrawText("ERROR: Invalid scene!", 200, 200, 30, RED);
    }
}
