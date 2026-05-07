#include "test_scene_1.h"
#include "../rbg_input/rbg_update_input.h"
#include "../rbg_scenes/rbg_scenes.h"
#include "../rbg_cam_control/rbg_cam_control.h"
#include "raylib.h"

void update_test_scene_1(void)
{
	if (IsInputActionPressed(INPUT_F1))
	{
		rbg_next_scene = TEST_SCENE_2;
	}

    DrawText("This is TEST SCENE 1", 0, 0, 30, WHITE);
}
