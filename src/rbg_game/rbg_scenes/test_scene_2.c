#include "test_scene_2.h"
#include "../rbg_input/rbg_update_input.h"
#include "../rbg_scenes/rbg_scenes.h"
#include "../rbg_cam_control/rbg_cam_control.h"
#include "../rbg_spritesheets/rbg_spritesheet_loader.h"
#include "../rbg_spritesheets/rbg_spritesheet_player.h"
#include "raylib.h"

static bool test_scene_2_initialized = false; 
static SpriteSheetPlayer sheetPlayer;
static SpriteSheetPlayer sheetPlayer_2;

void init_test_scene_2(void)
{
	rbg_global_camera.offset = (Vector2){ 100.0f, 300.0f };

	LoadSpriteSheets("resource/fighters_spritesheet_list.csv");

	InitSpriteSheetPlayer(&sheetPlayer, "fighter_0_idle", RBG_RENDER_PIVOT_CENTER);
	InitSpriteSheetPlayer(&sheetPlayer_2, "fighter_0_idle", RBG_RENDER_PIVOT_BOTTOM_CENTER);
}

void end_test_scene_2(void)
{
	// reset so we init again when we come back to this scene
	test_scene_2_initialized = false;
	UnloadSpriteSheets();
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
	UpdateSpriteSheetPlayer(&sheetPlayer_2);

	DrawSpriteSheetPlayer(&sheetPlayer, (Vector2){ 500.0f , 0.0f }, 1.0f, WHITE);
	DrawSpriteSheetPlayer(&sheetPlayer_2, (Vector2){ 800.0f, 0.0f }, 1.0f, GRAY);

	if (IsInputActionPressed(INPUT_F1))
	{
		rbg_next_scene = TEST_SCENE_1;
		end_test_scene_2();
	}

    DrawText("This is TEST SCENE 2", 0, 0, 30, WHITE);
}
