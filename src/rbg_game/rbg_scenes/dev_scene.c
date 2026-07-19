#include "dev_scene.h"
#include "../rbg_sprites/rbg_single_sprite_loader.h"
#include "../rbg_sprites/rbg_single_sprite_renderer.h"
#include <stdio.h>

void init_dev_scene(RbgGameContext* game_ctx)
{
	printf("\n=== starting dev scene ===\n");

	game_ctx->scene_initialized = true;

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
}

void render_dev_scene(RbgGameContext* game_ctx)
{
	rbg_render_single_sprite(game_ctx, "retro_cat_test", (Vector2){ 0.0f, 0.0f }, 3.0f, RENDER_PIVOT_BOTTOM_CENTER, GRAY);
}
