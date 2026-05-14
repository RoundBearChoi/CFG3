#ifndef RBG_PLAYERS_H
#define RBG_PLAYERS_H

#include "raylib.h"

// X macro for rbg_fighter_curr_state to convert enums to string literals.
// Should match png file (sheet) names exactly.
#define RBG_FIGHTER_STATES(X) \
	X(fighter_uninitialized) \
	X(fighter_0_idle) \
    X(fighter_0_walk_forward)

typedef enum
{
#define X(state) state,
    RBG_FIGHTER_STATES(X)
#undef X
    NUM_FIGHTER_STATES,
} rbg_fighter_state;

extern const char* const rbg_fighter_state_strings[NUM_FIGHTER_STATES];

typedef struct
{
    Vector2 position;
    bool is_facing_right_side;
	rbg_fighter_state fighter_curr_state;
	rbg_fighter_state fighter_prev_state;
} rbg_player;

extern rbg_player rbg_player_1;
extern rbg_player rbg_player_2;

void rbg_init_players(void);
void rbg_update_players(void);

#endif
