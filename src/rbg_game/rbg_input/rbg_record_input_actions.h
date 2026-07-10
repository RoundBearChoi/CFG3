#ifndef RBG_RECORD_INPUT_ACTIONS_H
#define RBG_RECORD_INPUT_ACTIONS_H

#include "../rbg_game_context.h"
#include "rbg_update_input.h"

void rbg_start_recording(RbgGameContext* game_ctx);
void rbg_stop_recording(RbgGameContext* game_ctx);
void rbg_update_recording(RbgGameContext* game_ctx);
bool rbg_save_recording(RbgGameContext* game_ctx, const char* filename);
bool rbg_input_action_is_pressed(RbgGameContext* game_ctx, InputAction action);

#endif
