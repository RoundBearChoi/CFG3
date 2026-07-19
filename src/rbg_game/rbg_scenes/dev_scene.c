#include "dev_scene.h"
#include "../rbg_scenes/rbg_scenes.h"
#include "../rbg_input/rbg_update_input.h"
#include "../rbg_sprites/rbg_single_sprite_loader.h"
#include "../rbg_sprites/rbg_single_sprite_renderer.h"
#include "raylib.h"
#include <stdio.h>

void init_dev_scene(RbgGameContext* game_ctx)
{
	printf("\n=== starting dev scene ===\n");

	game_ctx->scene_initialized = true;

	rbg_init_input(game_ctx);
	rbg_load_single_sprites(game_ctx, "resources/single_sprite_list.csv");
}

void end_dev_scene(RbgGameContext* game_ctx)
{
	game_ctx->scene_initialized = false;

	rbg_unload_single_sprites(game_ctx);
}

void update_dev_scene(RbgGameContext* game_ctx)
{
	if (game_ctx->scene_initialized == false)
	{
		init_dev_scene(game_ctx);
	}
	
	// temp - switch scene
	if (IsInputActionPressed(game_ctx, INPUT_F1))
	{
		printf("\nf1 pressed\n");
		rbg_set_next_scene(game_ctx, TEST_SCENE_2);
		end_dev_scene(game_ctx);
	}
}

void render_dev_scene(RbgGameContext* game_ctx)
{
	rbg_render_single_sprite(game_ctx, "text_dev_scene", (Vector2){ 0.0f, -400.0f }, 0.5f, RENDER_PIVOT_BOTTOM_CENTER, GREEN);
	rbg_render_single_sprite(game_ctx, "retro_cat_test", (Vector2){ 0.0f, 0.0f }, 3.0f, RENDER_PIVOT_BOTTOM_CENTER, GRAY);
}
