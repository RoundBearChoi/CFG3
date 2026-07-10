#include "test_scene_2.h"
#include "../rbg_input/rbg_update_input.h"
#include "../rbg_input/rbg_record_input_actions.h"
#include "../rbg_cam_control/rbg_cam_control.h"
#include "../rbg_players/rbg_players.h"
#include "../rbg_players/rbg_player_boxes.h"
#include "../rbg_players/rbg_basic_collision_resolve.h"
#include "../rbg_players/rbg_fighters/rbg_fighter_updater.h"
#include "../rbg_scenes/rbg_scenes.h"
#include "../rbg_spritesheets/rbg_sheet_loader.h" // need for unloading
#include "../rbg_spritesheets/rbg_sheet_animators.h"
#include "raylib.h"
#include <stdio.h>

static bool _test_scene_2_initialized = false; 

void init_test_scene_2(RbgGameContext* ctx)
{
	if (!ctx) return;

	printf("\n=== starting test scene 2 ===\n");

	_test_scene_2_initialized = true;

	rbg_init_input(ctx);
	rbg_init_players();
	rbg_init_player_boxes();
	rbg_init_sheet_animators();
}

void end_test_scene_2(RbgGameContext* ctx)
{
	if (!ctx) return;
	
	// reset so we init again when we come back to this scene
	_test_scene_2_initialized = false;

	rbg_stop_recording(ctx);
	rbg_unload_sprite_sheets();
}

void update_test_scene_2(RbgGameContext* ctx)
{
	if (!_test_scene_2_initialized) init_test_scene_2(ctx);

	rbg_update_recording(ctx); // input actions

	// temp - manual record button for now
	if (IsInputActionPressed(INPUT_F2)) rbg_start_recording(ctx);
	if (IsInputActionPressed(INPUT_F3))
	{
		rbg_stop_recording(ctx);
		rbg_save_recording("resources/recordings/demo_input.csv");  // nested array ready
	}

	// temp -  switch scene
	if (IsInputActionPressed(INPUT_F1))
	{
		rbg_set_next_scene(TEST_SCENE_1);
		end_test_scene_2(ctx);
	}
	
	// update all gameplay stuff
	rbg_update_cam_control(ctx);
	rbg_update_fighter(&rbg_player_1);
	rbg_update_fighter(&rbg_player_2);
	rbg_update_players();
	rbg_update_sheet_animators();
	rbg_update_player_boxes();
	rbg_update_basic_collision_resolve();
}

void render_test_scene_2(RbgGameContext* ctx)
{
	if (!ctx) return;
	
	rbg_draw_sprite_animation(&sheet_animator_p1, rbg_player_1.position, 1.0f, WHITE);
	rbg_draw_sprite_animation(&sheet_animator_p2, rbg_player_2.position, 1.0f, GRAY);
}
