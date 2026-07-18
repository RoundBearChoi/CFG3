#include "test_scene_2.h"
#include "../rbg_input/rbg_update_input.h"
#include "../rbg_input/rbg_record_input_actions.h"
#include "../rbg_cam_control/rbg_cam_control.h"
#include "../rbg_players/rbg_players.h"
#include "../rbg_players/rbg_player_boxes.h"
#include "../rbg_players/rbg_basic_collision_resolve.h"
#include "../rbg_players/rbg_fighters/rbg_fighter_updater.h"
#include "../rbg_scenes/rbg_scenes.h"
#include "../rbg_sprites/rbg_sheet_loader.h"
#include "../rbg_sprites/rbg_single_sprite_loader.h"
#include "../rbg_sprites/rbg_single_sprite_renderer.h"
#include "../rbg_sprites/rbg_sheet_animators.h"
#include "raylib.h"
#include <stdio.h>

void init_test_scene_2(RbgGameContext* game_ctx)
{
	printf("\n=== starting test scene 2 ===\n");

	game_ctx->scene_initialized = true;

	rbg_init_input(game_ctx);
	rbg_init_players(game_ctx);
	rbg_init_player_boxes(game_ctx);
	rbg_init_sheet_animators(game_ctx);
	rbg_init_fighter_update_functions();
}

void end_test_scene_2(RbgGameContext* game_ctx)
{
	printf("\n=== ending test scene 2 ===\n");

	game_ctx->scene_initialized = false;

	rbg_stop_recording(game_ctx);
	rbg_unload_sprite_sheets(game_ctx);
	rbg_unload_single_sprites(game_ctx);
}

void update_test_scene_2(RbgGameContext* game_ctx)
{
	if (game_ctx->scene_initialized == false)
	{
		init_test_scene_2(game_ctx);
	}

	rbg_update_recording(game_ctx); // input actions

	// temp - manual record button for now
	if (IsInputActionPressed(game_ctx, INPUT_F2)) rbg_start_recording(game_ctx);
	if (IsInputActionPressed(game_ctx, INPUT_F3))
	{
		rbg_stop_recording(game_ctx);
		rbg_save_recording(game_ctx, "resources/recordings/demo_input.csv");  // nested array ready
	}

	// temp - switch scene
	if (IsInputActionPressed(game_ctx, INPUT_F1))
	{
		rbg_set_next_scene(game_ctx, TEST_SCENE_1);
		end_test_scene_2(game_ctx);
	}
	
	// update all gameplay stuff
	rbg_update_cam_control(game_ctx);
	rbg_update_fighter(game_ctx, 1); //player 1
	rbg_update_fighter(game_ctx, 2); //player 2
	rbg_update_players();
	rbg_update_sheet_animators(game_ctx);
	rbg_update_player_boxes(game_ctx);
	rbg_update_basic_collision_resolve(game_ctx);
}

void render_test_scene_2(RbgGameContext* game_ctx)
{
	rbg_draw_sprite_animation(&game_ctx->sheet_animator_p1, game_ctx->player_1.position, 1.0f, WHITE);
	rbg_draw_sprite_animation(&game_ctx->sheet_animator_p2, game_ctx->player_2.position, 1.0f, GRAY);
	
	// cat test render
	rbg_render_single_sprite(game_ctx, "retro_cat_test", (Vector2){ 300.0f, -500.0f }, 3.0f, RENDER_PIVOT_CENTER, GRAY);
}
