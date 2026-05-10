#include "rbg_render_on_screenspace.h"
#include "rbg_game.h"
#include "rbg_fixed_update_count.h"
#include "rbg_scenes/rbg_input/rbg_record_input_actions.h"
#include "raylib.h"

extern Font press_start;

void rbg_render_on_screenspace(void)
{
	rbg_draw_scaled_text(TextFormat("FIXED UPDATE COUNT: %i", rbg_fixed_updates), (Vector2){ 10.0f, 10.0f }, 14.0f, WHITE);

	rbg_draw_scaled_text(TextFormat("RECORDING FRAME: %i", rbg_current_record_frame), (Vector2) { 10.0f, 50.0f }, 14.0f, WHITE);
}

void rbg_draw_scaled_text(const char* text, Vector2 pos, float fontSize, Color color)
{
    // Current render dimensions (updates automatically on resize/fullscreen)
    int screenHeight = GetScreenHeight();

    // Scale everything relative to 720p reference
    float scale = (float)screenHeight / 720.0f;

    fontSize = fontSize * scale;

	DrawTextEx(press_start,
               text,
               pos, // must be float
               fontSize, // must be float
               6, // spacing
               color);
}
