#include "raylib.h"
#include "rbg_render_debug.h"

void rbg_render_debug(void)
{
    // ── Mark world/screen origin (0, 0) with a bright red X
    const int crossSize = 25;
    const int thickness = 3;

    // Draw X at (0,0) — top-left corner of the window
    for (int i = 0; i < thickness; i++)
    {
        DrawLine(0, i, crossSize, crossSize + i, RED);
        DrawLine(i, 0, crossSize + i, crossSize, RED);
    }

    // Label so it's instantly obvious what we're looking at
    DrawText("(0,0)", crossSize + 5, 2, 10, RED);
}
