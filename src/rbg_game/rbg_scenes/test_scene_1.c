#include "test_scene_1.h"
#include "rbg_scenes.h"
#include "../rbg_input/rbg_update_input.h"
#include "../rbg_cam_control/rbg_cam_control.h"
#include "raylib.h"

void update_test_scene_1(RbgGameContext* ctx)
{
	if (!ctx) return;

	if (IsInputActionPressed(ctx, INPUT_F1))
	{
		rbg_set_next_scene(ctx, TEST_SCENE_2);
	}

	// Note: input, logic, state changes here. No drawing.
}

void render_test_scene_1(RbgGameContext* ctx)
{
	if (!ctx) return;

    DrawText("This is TEST SCENE 1", 0, 0, 30, WHITE);
	// All drawing / render commands for this scene go here.
}
