#ifndef RBG_PLAYERS_H
#define RBG_PLAYERS_H

#include "raylib.h"

// use X macro to convert to string literals. should match png file (sheet) names
typedef enum
{
	UNASSIGNED,

	fighter_0_idle,
	fighter_0_walk_forward,

	NUM_FIGHTER_STATES,
} rbg_fighter_state;

typedef struct
{
    Vector2 position;
    bool is_facing_right_side;
	rbg_fighter_state fighter_state;
} rbg_player;

extern rbg_player rbg_player_1;
extern rbg_player rbg_player_2;

void rbg_init_players(void);
void rbg_update_players(void);

#endif
