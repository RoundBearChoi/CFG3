#include "rbg_record_input_actions.h"
#include "raylib.h"
#include <string.h>
#include <stdlib.h>

// ====================== STATIC STATE ======================
static bool recordingBuffer[MAX_RECORD_FRAMES][NUM_RECORD_ACTIONS];
static int  currentRecordFrame = 0;
static bool isRecording = false;
static bool loggingDone = false;        // one-time initialization log
// =========================================================

void rbg_start_recording(void)
{
    // One-time system log (only the very first time recording is ever started)
    if (!loggingDone)
    {
        loggingDone = true;
        TraceLog(LOG_INFO, "Input recording system initialized (max %d frames @ 128 FPS)", MAX_RECORD_FRAMES);
    }

    // Always reset buffer and state when starting a new recording
    memset(recordingBuffer, 0, sizeof(recordingBuffer));
    currentRecordFrame = 0;
    isRecording = true;

    TraceLog(LOG_INFO, "=== INPUT RECORDING STARTED ===");
}

void rbg_stop_recording(void)
{
    if (!isRecording) return;

    isRecording = false;
    TraceLog(LOG_INFO, "=== INPUT RECORDING STOPPED === Recorded %d frames (%.2f seconds)",
             currentRecordFrame, currentRecordFrame / 128.0f);
}

bool rbg_is_recording(void)
{
    return isRecording;
}

int rbg_get_recorded_frames(void)
{
    return currentRecordFrame;
}

void rbg_update_recording(void)
{
    if (!isRecording) return;

    if (currentRecordFrame >= MAX_RECORD_FRAMES)
    {
        rbg_stop_recording();
        TraceLog(LOG_WARNING, "Maximum recording length (45s) reached");
        return;
    }

    // Record "pressed or held" state for each action
    for (int i = 0; i < NUM_RECORD_ACTIONS; i++)
    {
        InputAction action = (InputAction)(RECORD_FIRST_ACTION + i);
        recordingBuffer[currentRecordFrame][i] = IsInputActionDown(action);
    }

    currentRecordFrame++;
}

bool rbg_save_recording(const char* filename)
{
    if (currentRecordFrame <= 0)
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
    size_t estimated_size = 1024 + (size_t)currentRecordFrame * (NUM_RECORD_ACTIONS * 12 + 2);
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
    for (int f = 0; f < currentRecordFrame; f++)
    {
        for (int a = 0; a < NUM_RECORD_ACTIONS; a++)
        {
            if (a > 0)
                *ptr++ = ',';
            *ptr++ = recordingBuffer[f][a] ? '1' : '0';
        }
        *ptr++ = '\n';
    }
    *ptr = '\0';

    bool success = SaveFileText(filename, csvBuffer);
    free(csvBuffer);

    if (success)
    {
        TraceLog(LOG_INFO, "Input recording saved → %s (%d frames, %d actions) [CSV with header]",
                 filename, currentRecordFrame, NUM_RECORD_ACTIONS);
    }
    else
    {
        TraceLog(LOG_ERROR, "Failed to write recording file: %s", filename);
    }
    return success;
}
