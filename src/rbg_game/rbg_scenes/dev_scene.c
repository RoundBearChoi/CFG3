#include "dev_scene.h"

void init_dev_scene(RbgGameContext* game_ctx)
{
	printf("\n=== starting dev scene ===\n");

	game_ctx->scene_initialized = true;
}

void end_dev_scene(RbgGameContext* game_ctx)
{
	game_ctx->scene_initialized = false;
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
