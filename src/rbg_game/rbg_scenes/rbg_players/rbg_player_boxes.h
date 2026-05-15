#ifndef RBG_PLAYER_BOX_H
#define RBG_PLAYER_BOX_H

typedef struct
{
	int player_index;
	float pos_x;
	float pos_y;
	float width;
	float height;
	float offset_x;
	float offset_y;
} rbg_player_col_box;

extern rbg_player_col_box rbg_player_1_box;
extern rbg_player_col_box rbg_player_2_box;

#endif
