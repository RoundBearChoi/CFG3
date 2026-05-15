#include "rbg_render_debug.h"
#include "../rbg_game_settings.h"
#include "../rbg_scenes/rbg_players/rbg_players.h"
#include "../rbg_fixed_update_count.h"
#include "raylib.h"

void rbg_render_debug(void)
{
	if (rbg_game_settings.render_debug == false)
	{
		return;
	}

	// red x on (0, 0)
	// -y is up
	DrawLine(-5, 5, 5, -5, RED);
	DrawLine(-5, -5, 5, 5, RED);

	// random green horizontal line
	DrawLine(-50, -50, 50, -50, GREEN);

	// draw x on player positions
	Vector2 p1_pos = rbg_player_1.position;
	Vector2 p2_pos = rbg_player_2.position;

	Color p1_color_x = (Color){ 255, 247, 0, 255 };
	Color p2_color_x = (Color){ 255, 162, 0, 255 };

	int x_length = 5;

	DrawLineV((Vector2){p1_pos.x - x_length, p1_pos.y + x_length}, (Vector2){p1_pos.x + x_length, p1_pos.y - x_length}, p1_color_x);
	DrawLineV((Vector2){p1_pos.x - x_length, p1_pos.y - x_length}, (Vector2){p1_pos.x + x_length, p1_pos.y + x_length}, p1_color_x);

	DrawLineV((Vector2){p2_pos.x - x_length, p2_pos.y + x_length}, (Vector2){p2_pos.x + x_length, p2_pos.y - x_length}, p2_color_x);
	DrawLineV((Vector2){p2_pos.x - x_length, p2_pos.y - x_length}, (Vector2){p2_pos.x + x_length, p2_pos.y + x_length}, p2_color_x);
}
