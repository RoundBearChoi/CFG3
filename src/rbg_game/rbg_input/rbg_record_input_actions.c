#include "rbg_record_input_actions.h"
#include "raylib.h"
#include <string.h>
#include <stdlib.h>

//int global_rbg_current_record_frame = 0;

static bool _is_recording_input = false;
static bool _recording_buffer[MAX_RECORD_FRAMES][NUM_RECORD_ACTIONS];

void rbg_start_recording(RbgGameContext* game_ctx)
{
	TraceLog(LOG_INFO, "Input recording system initialized (max %d frames @ 128 FPS)", MAX_RECORD_FRAMES);

    // Always reset buffer and state when starting a new recording
    memset(_recording_buffer, 0, sizeof(_recording_buffer));
    game_ctx->current_recording_frame = 0; //global_rbg_current_record_frame = 0;
    _is_recording_input = true;

    TraceLog(LOG_INFO, "=== INPUT RECORDING STARTED ===");
}

void rbg_stop_recording(RbgGameContext* game_ctx)
{
    if (!_is_recording_input) return;

    _is_recording_input = false;
	game_ctx->current_recording_frame = 0; //global_rbg_current_record_frame = 0;
    
	TraceLog(LOG_INFO, "=== INPUT RECORDING STOPPED === Recorded %d frames (%.2f seconds)", game_ctx->current_recording_frame /*global_rbg_current_record_frame*/, game_ctx->current_recording_frame /*global_rbg_current_record_frame*/ / 128.0f);
}

void rbg_update_recording(RbgGameContext* game_ctx)
{
    if (!_is_recording_input) return;

    if (game_ctx->current_recording_frame /*global_rbg_current_record_frame*/ >= MAX_RECORD_FRAMES)
    {
        rbg_stop_recording(game_ctx);
        TraceLog(LOG_WARNING, "Maximum recording length (45s) reached");
        return;
    }

    // Record "pressed or held" state for each action
    for (int i = 0; i < NUM_RECORD_ACTIONS; i++)
    {
        InputAction action = (InputAction)(RECORD_FIRST_ACTION + i);
        _recording_buffer[game_ctx->current_recording_frame/*global_rbg_current_record_frame*/][i] = IsInputActionDown(action);
    }

    game_ctx->current_recording_frame++; //global_rbg_current_record_frame++;
}

bool rbg_save_recording(RbgGameContext* game_ctx, const char* filename)
{
    if (game_ctx->current_recording_frame /*global_rbg_current_record_frame*/ <= 0)
    {
        TraceLog(LOG_WARNING, "No frames recorded to save");
        return false;
    }
    if (!filename || filename[0] == '\0')
    {
        TraceLog(LOG_ERROR, "Invalid filename for recording save");
        return false;
    }

    // Rough but safe size estimate for CSV buffer
    size_t estimated_size = 1024 + (size_t)game_ctx->current_recording_frame  /*global_rbg_current_record_frame*/ * (NUM_RECORD_ACTIONS * 12 + 2);
    char* csvBuffer = (char*)malloc(estimated_size);
    if (!csvBuffer)
    {
        TraceLog(LOG_ERROR, "Failed to allocate memory for CSV buffer");
        return false;
    }

    char* ptr = csvBuffer;

    // === 1. WRITE HEADER ROW (column names) ===
    for (int a = 0; a < NUM_RECORD_ACTIONS; a++)
    {
        if (a > 0)
            *ptr++ = ',';

        InputAction action = (InputAction)(RECORD_FIRST_ACTION + a);
        const char* name = rbg_input_action_names[action];
        size_t len = strlen(name);
        memcpy(ptr, name, len);
        ptr += len;
    }
    *ptr++ = '\n';

    // === 2. WRITE DATA ROWS ===
    for (int f = 0; f < game_ctx->current_recording_frame /*global_rbg_current_record_frame*/; f++)
    {
        for (int a = 0; a < NUM_RECORD_ACTIONS; a++)
        {
            if (a > 0)
                *ptr++ = ',';
            *ptr++ = _recording_buffer[f][a] ? '1' : '0';
        }
        *ptr++ = '\n';
    }
    *ptr = '\0';

    bool success = SaveFileText(filename, csvBuffer);
    free(csvBuffer);

    if (success)
    {
        TraceLog(LOG_INFO, "Input recording saved → %s (%d frames, %d actions) [CSV with header]",
                 filename, game_ctx->current_recording_frame /*global_rbg_current_record_frame*/, NUM_RECORD_ACTIONS);
    }
    else
    {
        TraceLog(LOG_ERROR, "Failed to write recording file: %s", filename);
    }
    return success;
}

bool rbg_is_recording(void)
{
    return _is_recording_input;
}

bool rbg_input_action_is_pressed(RbgGameContext* game_ctx, InputAction action)
{
	// only during record (gameplay)
	if (_is_recording_input == false)
	{
		return false;
	}
    
    if (action < RECORD_FIRST_ACTION || action > RECORD_LAST_ACTION)
    {
        TraceLog(LOG_WARNING, "rbg_input_action_is_pressed: action %d is outside recorded range [%d-%d]",
                 (int)action, RECORD_FIRST_ACTION, RECORD_LAST_ACTION);
		
		return IsInputActionPressed(action); // fallback
	}

	int idx = (int)(action - RECORD_FIRST_ACTION);
    int frame = game_ctx->current_recording_frame;  // or whatever you're using

    if (frame <= 0) return false;

    return _recording_buffer[frame - 1][idx];	
}
