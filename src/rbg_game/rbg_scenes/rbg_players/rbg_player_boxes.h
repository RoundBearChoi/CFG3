#ifndef RBG_PLAYER_BOX_H
#define RBG_PLAYER_BOX_H

typedef struct
{
	int player_index;
	float width;
	float height;
	float offset_x;
	float offset_y;
} rbg_player_col_box;

extern rbg_player_col_box rbg_player_1_box;
extern rbg_player_col_box rbg_player_2_box;

void rbg_init_player_boxes();
void rbg_reset_box(rbg_player_col_box* box);
void rbg_update_player_boxes();

#endif
