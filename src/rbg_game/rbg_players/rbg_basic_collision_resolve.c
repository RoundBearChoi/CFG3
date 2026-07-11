#include "rbg_basic_collision_resolve.h"
#include "rbg_player_boxes.h"
#include "rbg_players.h"
#include "math.h"
#include <stddef.h>

void rbg_update_basic_collision_resolve(RbgGameContext* game_ctx)
{
	rbg_player* p1 = game_ctx->player_1; //rbg_get_player(1);
	rbg_player* p2 = game_ctx->player_2; //rbg_get_player(2);
	rbg_player_col_box* b1 = &(game_ctx->player_1_box);
	rbg_player_col_box* b2 = &(game_ctx->player_2_box);

	if (p1 == NULL || p2 == NULL || b1 == NULL || b2 == NULL)
	{
		return;
	}

	if (!b1->is_colliding_with_other_player || b1->overlap_x <= 0.0f)
	{
		return;
	}

	// Use pre-calculated overlap from detection (no need to rebuild rectangles)
	float push_amount = b1->overlap_x * 0.5f;

	if (p1->position.x < p2->position.x)
	{
		p1->position.x -= push_amount;
		p2->position.x += push_amount;
	}
	else
	{
		p1->position.x += push_amount;
		p2->position.x -= push_amount;
	}

	// Clear for next frame
	b1->is_colliding_with_other_player = false;
	b2->is_colliding_with_other_player = false;
	b1->overlap_x = 0.0f;
	b2->overlap_x = 0.0f;
}
