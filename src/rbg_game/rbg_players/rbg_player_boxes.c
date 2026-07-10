#include "rbg_player_boxes.h"
#include "rbg_players.h"
#include <stddef.h>
#include "raylib.h"
#include "math.h"

void rbg_init_player_boxes(RbgGameContext* game_ctx)
{
	rbg_reset_box(&game_ctx->player_1_box);
	rbg_reset_box(&game_ctx->player_2_box);

	game_ctx->player_1_box.player_index = 1;
	game_ctx->player_2_box.player_index = 2;
}

void rbg_reset_box(rbg_player_col_box* box)
{
	box->player_index = 0;
	box->is_colliding_with_other_player = false;
	box->width = 50.0f;
	box->height = 150.0f;
	box->offset_x = 0.0f;
	box->offset_y = 0.0f;
	box->overlap_x = 0.0f;
}

void rbg_update_player_boxes(RbgGameContext* game_ctx)
{
	rbg_check_collision(game_ctx);
}

void rbg_check_collision(RbgGameContext* game_ctx)
{
	rbg_player* p1 = rbg_get_player(1);
	rbg_player* p2 = rbg_get_player(2);
	rbg_player_col_box* b1 = &game_ctx->player_1_box;
	rbg_player_col_box* b2 = &game_ctx->player_2_box;

	if (p1 == NULL || p2 == NULL || b1 == NULL || b2 == NULL)
	{
		return;
	}

	// Player 1
	float effective_offset_x1 = b1->offset_x;
	if (!p1->is_facing_right_side)
	{
		effective_offset_x1 = -b1->offset_x;
	}
	float box1_cx = p1->position.x + effective_offset_x1;
	float box1_by = p1->position.y + b1->offset_y;

	Rectangle rect1 =
	{
		.x = box1_cx - (b1->width * 0.5f),
		.y = box1_by - b1->height,
		.width = b1->width,
		.height = b1->height
	};

	// Player 2
	float effective_offset_x2 = b2->offset_x;
	if (!p2->is_facing_right_side)
	{
		effective_offset_x2 = -b2->offset_x;
	}
	float box2_cx = p2->position.x + effective_offset_x2;
	float box2_by = p2->position.y + b2->offset_y;

	Rectangle rect2 =
	{
		.x = box2_cx - (b2->width * 0.5f),
		.y = box2_by - b2->height,
		.width = b2->width,
		.height = b2->height
	};

	bool is_colliding = CheckCollisionRecs(rect1, rect2);

	float overlap = 0.0f;
	if (is_colliding)
	{
		float overlap_left  = fmaxf(rect1.x, rect2.x);
		float overlap_right = fminf(rect1.x + rect1.width, rect2.x + rect2.width);
		overlap = overlap_right - overlap_left;
	}

	// Store results
	b1->is_colliding_with_other_player = is_colliding;
	b2->is_colliding_with_other_player = is_colliding;
	b1->overlap_x = overlap;
	b2->overlap_x = overlap;
}

rbg_player_col_box* rbg_get_player_box(RbgGameContext* game_ctx, int playerIndex)
{
	if (playerIndex == 1)
	{
		return &game_ctx->player_1_box;
	}
	else if (playerIndex == 2)
	{
		return &game_ctx->player_2_box;
	}

	return NULL;
}
