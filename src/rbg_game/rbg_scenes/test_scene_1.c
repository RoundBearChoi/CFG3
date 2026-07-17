#include "test_scene_1.h"
#include "rbg_scenes.h"
#include "../rbg_input/rbg_update_input.h"
#include "../rbg_cam_control/rbg_cam_control.h"
#include "raylib.h"

void init_test_scene_1(RbgGameContext* game_ctx)
{
	printf("\n=== starting test scene 1 ===\n");

	game_ctx->scene_initialized = true;
}

void end_test_scene_1(RbgGameContext* game_ctx)
{
	printf("\n=== ending test scene 1 ===\n");

	game_ctx->scene_initialized = false;
}

void update_test_scene_1(RbgGameContext* game_ctx)
{
	if (game_ctx->scene_initialized == false)
	{
		init_test_scene_1(game_ctx);
	}

	if (IsInputActionPressed(game_ctx, INPUT_F1))
	{
		rbg_set_next_scene(game_ctx, TEST_SCENE_2);
		end_test_scene_1(game_ctx);
	}
}

void render_test_scene_1(RbgGameContext* game_ctx)
{
	if (!game_ctx) return;

    DrawText("This is TEST SCENE 1", 0, 0, 30, WHITE);
}
