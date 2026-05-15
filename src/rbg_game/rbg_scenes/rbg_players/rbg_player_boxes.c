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
	box->width = 20.0f;
	box->height = 60.0f;
	box->offset_x = 0.0f;
	box->offset_y = 0.0f;
}

void rbg_update_player_boxes()
{

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
