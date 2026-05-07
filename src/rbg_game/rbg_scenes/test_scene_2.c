#include "test_scene_2.h"
#include "../rbg_cam_control/rbg_cam_control.h"
#include "../rbg_spritesheets/rbg_spritesheet_loader.h"
#include "raylib.h"

static bool test_scene_2_initialized = false; 

void init_test_scene_2(void)
{
	LoadSpritesheets("resource/fighters_spritesheet_list.csv");
}

void update_test_scene_2(void)
{
	if (test_scene_2_initialized == false)
	{
		test_scene_2_initialized = true;
		init_test_scene_2();
	}

	rbg_update_cam_control();

    DrawText("This is TEST SCENE 2", 0, 0, 30, WHITE);
}
