#include "rbg_render_on_screenspace.h"
#include "rbg_fixed_update_count.h"
#include "rbg_scenes/rbg_input/rbg_record_input_actions.h"
#include "raylib.h"

void rbg_render_on_screenspace(void)
{
	rbg_draw_scaled_text(TextFormat("fixed update count: %i", rbg_fixed_updates), 10, 10, 16, WHITE);

	rbg_draw_scaled_text(TextFormat("recording frame: %i", rbg_current_record_frame), 10, 30, 16, WHITE);
}

void rbg_draw_scaled_text(const char* text, int baseX, int baseY, int fontSize, Color color)
{
    // Current render dimensions (updates automatically on resize/fullscreen)
    int screenHeight = GetScreenHeight();

    // Scale everything relative to 720p reference
    float scale = (float)screenHeight / 720.0f;

    fontSize = (int)(fontSize * scale + 0.5f);   // matches original font size

    int x = (int)(baseX * scale + 0.5f);
    int y = (int)(baseY * scale + 0.5f);

    DrawText(text, x, y, fontSize, color);
}
