#include "test_scene_2.h"
#include "../rbg_cam_control/rbg_cam_control.h"
#include "../rbg_spritesheets/rbg_spritesheet_loader.h"
#include "../rbg_spritesheets/rbg_spritesheet_player.h"
#include "raylib.h"

static bool test_scene_2_initialized = false; 
static SpriteSheetPlayer sheetPlayer;

void init_test_scene_2(void)
{
	LoadSpriteSheets("resource/fighters_spritesheet_list.csv");

	InitSpriteSheetPlayer(&sheetPlayer, "fighter_0_sample");
}

void update_test_scene_2(void)
{
	if (test_scene_2_initialized == false)
	{
		test_scene_2_initialized = true;
		init_test_scene_2();
	}

	rbg_update_cam_control();

	UpdateSpriteSheetPlayer(&sheetPlayer);
	DrawSpriteSheetPlayer(&sheetPlayer, (Vector2){400, 300}, 1.0f, WHITE);

    DrawText("This is TEST SCENE 2", 0, 0, 30, WHITE);
}
