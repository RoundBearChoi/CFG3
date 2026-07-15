#include "rbg_render_on_screenspace.h"
#include "rbg_game.h"
#include "rbg_game_settings.h"
#include "rbg_input/rbg_record_input_actions.h"
#include "raylib.h"

extern Font global_font_press_start;

void rbg_render_on_screenspace(RbgGameContext* game_ctx)
{
	if (global_rbg_game_settings.render_debug == false)
	{
		return;
	}

	rbg_draw_on_test_scene_2(game_ctx);
}

void rbg_draw_scaled_text(const char* text, Vector2 pos, float font_size, float font_spacing, Color color)
{
	DrawTextEx(global_font_press_start,
               text,
               pos, // must be float
               font_size, // must be float
               font_spacing, // must be float
               color);
}

void rbg_draw_on_test_scene_2(RbgGameContext* game_ctx)
{
	if (game_ctx->current_scene != TEST_SCENE_2)
	{
		return;
	}

	// scale to 720p reference
    int screenHeight = GetScreenHeight();
    float scale = (float)screenHeight / 720.0f;
	float font_size = 15.0f * scale;
	float font_spacing = 3.0f * scale;
	float horizontal_gap = 20.0f * scale;

	rbg_draw_scaled_text(TextFormat("FIXED UPDATE COUNT: %i", game_ctx->fps_display), (Vector2){ 10.0f, 15.0f }, font_size, font_spacing, WHITE);
	rbg_draw_scaled_text(TextFormat("RECORDING FRAME: %i", game_ctx->current_recording_frame), (Vector2){ 10.0f, 15.0f + horizontal_gap }, font_size, font_spacing, WHITE);
	rbg_draw_scaled_text(TextFormat("PRESS F2 TO START PLAYING, F3 TO STOP"), (Vector2){ 10.0f, 15.0f + horizontal_gap * 2 }, font_size, font_spacing, WHITE);
	rbg_draw_scaled_text(TextFormat("F11 TO CYCLE THROUGH WINDOW MODES"), (Vector2){ 10.0f, 15.0f + horizontal_gap * 3 }, font_size, font_spacing, WHITE);
}
