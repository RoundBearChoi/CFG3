#include "rbg_cam_control.h"
#include "../rbg_input/rbg_update_input.h"
#include "raylib.h"

// specific to test_scene_2
void rbg_init_cam_control(RbgGameContext* ctx)
{
	if (!ctx) return;

	ctx->camera.offset = (Vector2){ 0.0f, 0.0f };
	ctx->camera.target = (Vector2){ -600.0f, -600.0f }; // behaves like camera position
	ctx->camera.rotation = 0.0f;
	ctx->camera.zoom = 1.0f;
}

// specific to test_scene_2
void rbg_update_cam_control(RbgGameContext* ctx)
{
	if (!ctx) return;
}
