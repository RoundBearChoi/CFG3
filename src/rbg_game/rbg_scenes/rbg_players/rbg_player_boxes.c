#include "rbg_player_boxes.h"
#include "rbg_players.h"
#include <stddef.h>

rbg_player_col_box rbg_player_1_box;
rbg_player_col_box rbg_player_2_box;

void rbg_init_player_boxes()
{
	rbg_reset_box(&rbg_player_1_box);
	rbg_reset_box(&rbg_player_2_box);

	rbg_player_1_box.player_index = 1;
	rbg_player_2_box.player_index = 2;
}

void rbg_reset_box(rbg_player_col_box* box)
{
	box->player_index = 0;
	box->collision_with_other_player = false;
	box->width = 20.0f;
	box->height = 60.0f;
	box->offset_x = 0.0f;
	box->offset_y = 0.0f;
}

void rbg_update_player_boxes()
{
	rbg_player* p1 = rbg_get_player(1);
    rbg_player* p2 = rbg_get_player(2);
    rbg_player_col_box* b1 = rbg_get_player_box(1);
    rbg_player_col_box* b2 = rbg_get_player_box(2);

    // should never happen with valid indices, but defensive
    if (p1 == NULL || p2 == NULL || b1 == NULL || b2 == NULL)
    {
        return;
    }

    // Player 1: bottom-center based AABB with facing-aware offset mirroring
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

    // Player 2: same logic
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

    // AABB test using raylib's built-in function
    bool is_colliding = CheckCollisionRecs(rect1, rect2);

    // Update collision flags for both players
    b1->collision_with_other_player = is_colliding;
    b2->collision_with_other_player = is_colliding;
}

rbg_player_col_box* rbg_get_player_box(int playerIndex)
{
	if (playerIndex == 1)
	{
		return &rbg_player_1_box;
	}
	else if (playerIndex == 2)
	{
		return &rbg_player_2_box;
	}

	return NULL;
}
