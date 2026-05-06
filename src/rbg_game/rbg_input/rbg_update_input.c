#include "rbg_update_input.h"
#include "raylib.h"

extern Camera2D rbg_global_camera;

void rbg_update_input(void)
{
	if (IsKeyDown(KEY_RIGHT))
	{
		DrawText("key right pressed", 0, 50, 30, WHITE);

		rbg_global_camera.offset.x += 1;
	}
}
