#include "test_scene_2.h"
#include "rbg_input/rbg_update_input.h"
#include "rbg_input/rbg_record_input_actions.h"
#include "../rbg_scenes/rbg_scenes.h"
#include "rbg_cam_control/rbg_cam_control.h"
#include "../rbg_spritesheets/rbg_spritesheet_loader.h"
#include "../rbg_spritesheets/rbg_spritesheet_player.h"
#include "rbg_players/rbg_players.h"
#include "raylib.h"
#include <stdio.h>

static bool test_scene_2_initialized = false; 
static SpriteSheetPlayer sheetPlayer;
static SpriteSheetPlayer sheetPlayer_2;

void init_test_scene_2(void)
{
	printf("\n=== starting test scene 2 ===\n");

	test_scene_2_initialized = true;

	rbg_load_sprite_sheets("resources/fighters_spritesheet_list.csv");
	
	rbg_init_input();
	rbg_init_cam_control();
	rbg_init_players();

	// temp - update can get info from player. probably won't need separate init
	rbg_init_sprite_sheet(&sheetPlayer, "fighter_0_idle", RENDER_PIVOT_BOTTOM_CENTER);
	rbg_init_sprite_sheet(&sheetPlayer_2, "fighter_0_idle", RENDER_PIVOT_BOTTOM_CENTER);

	// temp testing
	sheetPlayer_2.is_facing_right_side = false;
}

void end_test_scene_2(void)
{
	// reset so we init again when we come back to this scene
	test_scene_2_initialized = false;

	rbg_stop_recording();
	rbg_unload_sprite_sheets();
}

void update_test_scene_2(void)
{
	if (!test_scene_2_initialized) init_test_scene_2();

	rbg_update_recording(); // input actions

	// temp - manual record button for now
	if (IsInputActionPressed(INPUT_F2)) rbg_start_recording();
	if (IsInputActionPressed(INPUT_F3))
	{
		rbg_stop_recording();
		rbg_save_recording("resources/recordings/demo_input.csv");  // nested array ready
	}

	rbg_update_cam_control();
	rbg_update_players();
	rbg_update_sprite_sheet(&sheetPlayer);
	rbg_update_sprite_sheet(&sheetPlayer_2);

	rbg_draw_sprite_sheet(&sheetPlayer, rbg_player_1.position, 1.0f, WHITE);
	rbg_draw_sprite_sheet(&sheetPlayer_2, (Vector2){ 400.0f, 0.0f }, 1.0f, GRAY);

	if (IsInputActionPressed(INPUT_F1))
	{
		rbg_next_scene = TEST_SCENE_1;
		end_test_scene_2();
	}
}
