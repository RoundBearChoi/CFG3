#include "rbg_cam_control.h"
#include "../rbg_input/rbg_update_input.h"
#include "raylib.h"

void rbg_init_cam_control(RbgGameContext* game_ctx)
{
	if (game_ctx->cam_initialized == false)
	{
		//game_ctx->camera.offset = (Vector2){ 0.0f, 0.0f };
		//game_ctx->camera.target = (Vector2){ -600.0f, -600.0f }; // behaves like camera position
		//game_ctx->camera.rotation = 0.0f;
		//game_ctx->camera.zoom = 1.0f;

		game_ctx->cam_initialized = true;
	}
}

void rbg_update_cam_control(RbgGameContext* game_ctx)
{
	rbg_init_cam_control(game_ctx);
}
