#include "test_scene_1.h"
#include "../rbg_cam_control/rbg_cam_control.h"
#include "raylib.h"

void update_test_scene_1(void)
{
	rbg_update_cam_control();

    DrawText("This is TEST SCENE 1", 0, 0, 30, WHITE);
}
