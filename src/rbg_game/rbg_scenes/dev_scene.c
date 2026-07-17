#include "dev_scene.h"

void init_dev_scene(RbgGameContext* game_ctx)
{
	printf("\n=== starting dev scene ===\n");

	game_ctx->scene_initialized = true;

	//rbg_init_input(game_ctx);
	//rbg_init_players(game_ctx);
	//rbg_init_player_boxes(game_ctx);
	//rbg_init_sheet_animators(game_ctx);
	//rbg_init_fighter_update_functions();
}

void end_dev_scene(RbgGameContext* game_ctx)
{
	game_ctx->scene_initialized = false;

	//rbg_stop_recording(game_ctx);
	//rbg_unload_sprite_sheets(game_ctx);
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

}
