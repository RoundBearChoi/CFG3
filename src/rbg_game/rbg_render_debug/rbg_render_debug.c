#include "rbg_render_debug.h"
#include "../rbg_game_settings.h"
#include "../rbg_players/rbg_players.h"
#include "../rbg_players/rbg_player_boxes.h"
#include <stddef.h>
#include "raylib.h"

void rbg_render_debug(RbgGameContext* game_ctx)
{
	if (global_rbg_game_settings.render_debug == false) { return; }

	if (game_ctx->current_scene != TEST_SCENE_2) { return; } //temp - only draw on test_scene_2 for now

	// red x on (0, 0)
	// -y is up
	DrawLine(-5, 5, 5, -5, RED);
	DrawLine(-5, -5, 5, 5, RED);

	// random green horizontal line
	DrawLine(-50, -50, 50, -50, GREEN);

	rbg_draw_player_box(game_ctx, 1);
	rbg_draw_player_box(game_ctx, 2);
	rbg_draw_x_on_player_pos(game_ctx);
}

void rbg_draw_x_on_player_pos(RbgGameContext* game_ctx)
{
	// draw x on player positions
	Vector2 p1_pos = game_ctx->player_1.position;
	Vector2 p2_pos = game_ctx->player_2.position;

	Color p1_color_x = (Color){ 0, 149, 255, 255 };
	Color p2_color_x = (Color){ 255, 162, 0, 255 };

	int x_length = 8;

	DrawLineV((Vector2){ p1_pos.x - x_length, p1_pos.y + x_length }, (Vector2){ p1_pos.x + x_length, p1_pos.y - x_length }, p1_color_x);
	DrawLineV((Vector2){ p1_pos.x - x_length, p1_pos.y - x_length }, (Vector2){ p1_pos.x + x_length, p1_pos.y + x_length }, p1_color_x);

	DrawLineV((Vector2){ p2_pos.x - x_length, p2_pos.y + x_length }, (Vector2){ p2_pos.x + x_length, p2_pos.y - x_length }, p2_color_x);
	DrawLineV((Vector2){ p2_pos.x - x_length, p2_pos.y - x_length }, (Vector2){ p2_pos.x + x_length, p2_pos.y + x_length }, p2_color_x);
}

void rbg_draw_player_box(RbgGameContext* game_ctx, int playerIndex)
{
	rbg_player* p = rbg_get_player(game_ctx, playerIndex); 
	rbg_player_col_box* b = rbg_get_player_box(game_ctx, playerIndex);

	float center_x = p->position.x + b->offset_x;
	float bottom_y = p->position.y + b->offset_y;

	// -y is up, top of the box is below the bottom in y terms
	float top_y  = bottom_y - b->height;
	float left_x = center_x - (b->width * 0.5f);

	Rectangle rec = { left_x, top_y, b->width, b->height };
	
	Color boxColor = (Color){ 255, 234, 0, 255 };

	if (b->is_colliding_with_other_player)
	{
		boxColor = (Color){ 255, 0, 0, 255 };
	}

	DrawRectangleLinesEx(rec, 0.9f, boxColor);
}
