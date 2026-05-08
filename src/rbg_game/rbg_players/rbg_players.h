#ifndef RBG_PLAYERS_H
#define RBG_PLAYERS_H

#include "raylib.h"

typedef struct
{
    Vector2 position;
    bool is_facing_right_side;
} rbg_player;

extern rbg_player rbg_player_1;
extern rbg_player rbg_player_2;

void rbg_init_players(void);
void rbg_update_players(void);

#endif
