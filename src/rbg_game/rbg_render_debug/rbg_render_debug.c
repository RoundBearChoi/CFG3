#include "rbg_render_debug.h"
#include "../rbg_players/rbg_players.h"
#include "raylib.h"

void rbg_render_debug(void)
{
	// red x on (0, 0)
	// -y is up
	DrawLine(-10, 10, 10, -10, RED);
	DrawLine(-10, -10, 10, 10, RED);

	// random green horizontal line
	DrawLine(-50, -50, 50, -50, GREEN);

	// draw yellow x on player position
	Vector2 p1_pos = rbg_player_1.position;
	Vector2 p2_pos = rbg_player_2.position;

	Color p1_color_x = (Color){ 255, 247, 0, 255 };
	Color p2_color_x = (Color){ 255, 162, 0, 255 };

	DrawLineV((Vector2){p1_pos.x - 10, p1_pos.y + 10}, (Vector2){p1_pos.x + 10, p1_pos.y - 10}, p1_color_x);
	DrawLineV((Vector2){p1_pos.x - 10, p1_pos.y - 10}, (Vector2){p1_pos.x + 10, p1_pos.y + 10}, p1_color_x);

	DrawLineV((Vector2){p2_pos.x - 10, p2_pos.y + 10}, (Vector2){p2_pos.x + 10, p2_pos.y - 10}, p2_color_x);
	DrawLineV((Vector2){p2_pos.x - 10, p2_pos.y - 10}, (Vector2){p2_pos.x + 10, p2_pos.y + 10}, p2_color_x);
}
