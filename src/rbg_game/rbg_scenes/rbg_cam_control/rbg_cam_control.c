#include "rbg_cam_control.h"
#include "../../rbg_input/rbg_update_input.h"
#include "raylib.h"

// Definition (no extern) – this is the real variable
Camera2D rbg_global_camera;

void rbg_init_cam_control(void)
{
	rbg_global_camera.rotation = 0.0f;
	rbg_global_camera.zoom     = 1.0f;
}

void rbg_update_cam_control(void)
{
	// temp - only for testing
	/*
	if (IsInputActionDown(INPUT_P1_MOVE_LEFT))
	{
		rbg_global_camera.offset.x += 1;
	}

	if (IsInputActionDown(INPUT_P1_MOVE_RIGHT))
	{
		rbg_global_camera.offset.x -= 1;
	}

	if (IsInputActionDown(INPUT_P1_MOVE_UP))
	{
		rbg_global_camera.offset.y += 1;
	}

	if (IsInputActionDown(INPUT_P1_MOVE_DOWN))
	{
		rbg_global_camera.offset.y -= 1;
	}
	*/
}
