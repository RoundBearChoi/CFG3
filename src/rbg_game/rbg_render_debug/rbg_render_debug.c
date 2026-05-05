#include "rbg_render_debug.h"
#include "raylib.h"

void rbg_render_debug(void)
{
	// red x on (0, 0)
	// -y is up
	DrawLine(-10, 10, 10, -10, RED);
	DrawLine(-10, -10, 10, 10, RED);

	// random green horizontal line
	DrawLine(-50, -50, 50, -50, GREEN);
}
