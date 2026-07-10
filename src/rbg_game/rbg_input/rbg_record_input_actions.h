#ifndef RBG_RECORD_INPUT_ACTIONS_H
#define RBG_RECORD_INPUT_ACTIONS_H

#include "../rbg_game_context.h"
#include "rbg_update_input.h"

// ====================== CONFIG ======================
#define MAX_RECORD_FRAMES     (45 * 128) // 5760 frames (45 seconds @ 128 FPS)
#define RECORD_FIRST_ACTION   INPUT_P1
#define RECORD_LAST_ACTION    END_OF_INPUT
#define NUM_RECORD_ACTIONS    ((int)(RECORD_LAST_ACTION - RECORD_FIRST_ACTION + 1))
// ===================================================

extern int global_rbg_current_record_frame;

void rbg_start_recording(RbgGameContext* game_ctx);
void rbg_stop_recording(RbgGameContext* game_ctx);
bool rbg_is_recording(void);
int  rbg_get_recorded_frames(void);
void rbg_update_recording(RbgGameContext* game_ctx);
bool rbg_save_recording(RbgGameContext* game_ctx, const char* filename);
bool rbg_input_action_is_pressed(InputAction action);

#endif
