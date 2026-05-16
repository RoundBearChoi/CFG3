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

    // Safety guard (should never happen with valid indices, but defensive)
    if (p1 == NULL || p2 == NULL || b1 == NULL || b2 == NULL) {
        return;
    }

    // Calculate Player 1's AABB (top-left based, with facing mirror)
    float rect1_x = p1->position.x + b1->offset_x;
    if (!p1->is_facing_right_side) {
        rect1_x = p1->position.x - (b1->offset_x + b1->width);
    }
    Rectangle rect1 = {
        .x = rect1_x,
        .y = p1->position.y + b1->offset_y,
        .width = b1->width,
        .height = b1->height
    };

    // Calculate Player 2's AABB (top-left based, with facing mirror)
    float rect2_x = p2->position.x + b2->offset_x;
    if (!p2->is_facing_right_side) {
        rect2_x = p2->position.x - (b2->offset_x + b2->width);
    }
    Rectangle rect2 = {
        .x = rect2_x,
        .y = p2->position.y + b2->offset_y,
        .width = b2->width,
        .height = b2->height
    };

    // Perform the AABB test using raylib's built-in function
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
