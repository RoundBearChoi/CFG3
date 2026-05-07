#include "test_scene_2.h"
#include "../rbg_input/rbg_update_input.h"
#include "../rbg_cam_control/rbg_cam_control.h"
#include "../rbg_spritesheets/rbg_spritesheet_loader.h"
#include "../rbg_spritesheets/rbg_spritesheet_player.h"
#include "raylib.h"

static bool test_scene_2_initialized = false; 
static SpriteSheetPlayer sheetPlayer;

void init_test_scene_2(void)
{
	LoadSpriteSheets("resource/fighters_spritesheet_list.csv");

	InitSpriteSheetPlayer(&sheetPlayer, "fighter_0_idle");
}

void end_test_scene_2(void)
{

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

	if (IsInputActionDown(INPUT_F1))
	{
		//DrawText("F1 key is working", 0, 100, 30, WHITE);
	}

    DrawText("This is TEST SCENE 2", 0, 0, 30, WHITE);
}
