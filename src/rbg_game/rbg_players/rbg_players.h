#ifndef RBG_PLAYERS_H
#define RBG_PLAYERS_H

#include "../rbg_game_context.h"
#include "raylib.h"

void rbg_init_players(RbgGameContext* game_ctx);
void rbg_update_players(void);
bool new_state_detected(rbg_player* player);
rbg_player* rbg_get_player(RbgGameContext* game_ctx, int playerIndex);

#endif
