#ifndef RBG_GAME_CONTEXT_H
#define RBG_GAME_CONTEXT_H

#include <stdbool.h>
#include "raylib.h"

typedef struct {
    bool game_initialized;

    // fixed timestep state
    double accumulator;
    double previous_time;
    double fixed_dt;

	// cam ctx
	Camera2D camera;
	bool cam_initialized;

	// input ctx
	int current_recording_frame;
	bool is_recording_input;
} RbgGameContext;

#endif
