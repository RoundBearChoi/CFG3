#include "rbg_render_debug.h"
#include "../rbg_game_settings.h"
#include "../rbg_scenes/rbg_players/rbg_players.h"
#include "../rbg_scenes/rbg_players/rbg_player_boxes.h"
#include "../rbg_fixed_update_count.h"
#include "raylib.h"

void rbg_render_debug(void)
{
	if (rbg_game_settings.render_debug == false) { return; }

	// red x on (0, 0)
	// -y is up
	DrawLine(-5, 5, 5, -5, RED);
	DrawLine(-5, -5, 5, 5, RED);

	// random green horizontal line
	DrawLine(-50, -50, 50, -50, GREEN);

	rbg_draw_player_boxes(1);
	rbg_draw_player_boxes(2);
	rbg_draw_x_on_player_pos();
}

void rbg_draw_x_on_player_pos(void)
{
	// draw x on player positions
	Vector2 p1_pos = rbg_player_1.position;
	Vector2 p2_pos = rbg_player_2.position;

	Color p1_color_x = (Color){ 0, 149, 255, 255 };
	Color p2_color_x = (Color){ 255, 162, 0, 255 };

	int x_length = 3.2;

	DrawLineV((Vector2){ p1_pos.x - x_length, p1_pos.y + x_length }, (Vector2){ p1_pos.x + x_length, p1_pos.y - x_length }, p1_color_x);
	DrawLineV((Vector2){ p1_pos.x - x_length, p1_pos.y - x_length }, (Vector2){ p1_pos.x + x_length, p1_pos.y + x_length }, p1_color_x);

	DrawLineV((Vector2){ p2_pos.x - x_length, p2_pos.y + x_length }, (Vector2){ p2_pos.x + x_length, p2_pos.y - x_length }, p2_color_x);
	DrawLineV((Vector2){ p2_pos.x - x_length, p2_pos.y - x_length }, (Vector2){ p2_pos.x + x_length, p2_pos.y + x_length }, p2_color_x);
}

void rbg_draw_player_boxes(int playerIndex)
{
	rbg_player* p = rbg_get_player(playerIndex); 
	rbg_player_col_box* b = rbg_get_player_box(playerIndex);

	float center_x = p->position.x + b->offset_x;
	float bottom_y = p->position.y + b->offset_y;

	// -y is up, top of the box is below the bottom in y terms
	float top_y  = bottom_y - b->height;
	float left_x = center_x - (b->width * 0.5f);

	Rectangle rec = { left_x, top_y, b->width, b->height };
	
	Color boxColor = (Color){ 255, 234, 0, 255 };

	if (b->collision_with_other_player)
	{
		boxColor = (Color){ 255, 0, 0, 255 };
	}

	DrawRectangleLinesEx(rec, 0.9f, boxColor);
	//DrawRectangleRec(rec, (Color){ 255, 234, 0, 80 });
}
