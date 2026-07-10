#ifndef RBG_PLAYERS_H
#define RBG_PLAYERS_H

#include "raylib.h"

typedef enum
{
	fighter_uninitialized,
	fighter_0_idle,
    fighter_0_walk,
    fighter_0_jump,
    fighter_0_fall,
    NUM_FIGHTER_STATES,
} rbg_fighter_state;

typedef struct
{
	int player_index;
    Vector2 position;
    bool is_facing_right_side;
	rbg_fighter_state fighter_curr_state;
	rbg_fighter_state fighter_prev_state;
} rbg_player;

extern rbg_player rbg_player_1;
extern rbg_player rbg_player_2;

void rbg_init_players(void);
void rbg_update_players(void);
bool new_state_detected(rbg_player* player);
rbg_player* rbg_get_player(int playerIndex);

#endif
