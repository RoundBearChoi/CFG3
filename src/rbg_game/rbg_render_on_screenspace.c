#include "rbg_render_on_screenspace.h"
#include "rbg_fixed_update_count.h"
#include "raylib.h"

void rbg_render_on_screenspace(void)
{
	DrawText(TextFormat("fixed update count: %i", rbg_fixed_updates), 10, 10, 20, GREEN);
}
