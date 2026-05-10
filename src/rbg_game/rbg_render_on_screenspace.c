#include "rbg_render_on_screenspace.h"
#include "rbg_game.h"
#include "rbg_fixed_update_count.h"
#include "rbg_scenes/rbg_input/rbg_record_input_actions.h"
#include "raylib.h"

extern Font press_start;

void rbg_render_on_screenspace(void)
{
	// scale 720p reference
    int screenHeight = GetScreenHeight();
    float scale = (float)screenHeight / 720.0f;
	float font_size = 16.0f * scale;
	float font_spacing = 3.0f * scale;
	float horizontal_gap = 20.0f * scale;

	rbg_draw_scaled_text(TextFormat("FIXED UPDATE COUNT: %i", rbg_fixed_updates), (Vector2){ 10.0f, 15.0f }, font_size, font_spacing, WHITE);

	rbg_draw_scaled_text(TextFormat("RECORDING FRAME: %i", rbg_current_record_frame), (Vector2){ 10.0f, 15.0f + horizontal_gap }, font_size, font_spacing, WHITE);
}

void rbg_draw_scaled_text(const char* text, Vector2 pos, float font_size, float font_spacing, Color color)
{
	DrawTextEx(press_start,
               text,
               pos, // must be float
               font_size, // must be float
               font_spacing, // must be float
               color);
}
