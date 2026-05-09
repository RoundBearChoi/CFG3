#ifndef RBG_RECORD_INPUT_ACTIONS_H
#define RBG_RECORD_INPUT_ACTIONS_H

#include "rbg_update_input.h"   // for InputAction and IsInputActionDown

// ====================== CONFIG ======================
#define MAX_RECORD_FRAMES     (45 * 128) // 5760 frames (45 seconds @ 128 FPS)
#define RECORD_FIRST_ACTION   INPUT_P1_MOVE_LEFT
#define RECORD_LAST_ACTION    INPUT_P1_ATTACK
#define NUM_RECORD_ACTIONS    ((int)(RECORD_LAST_ACTION - RECORD_FIRST_ACTION + 1))
// ===================================================

extern int rbg_current_record_frame;
extern bool rbg_is_recording_input;

void rbg_start_recording(void);
void rbg_stop_recording(void);
bool rbg_is_recording(void);
void rbg_update_recording(void);
int  rbg_get_recorded_frames(void);
bool rbg_save_recording(const char* filename);

#endif
