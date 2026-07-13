#ifndef RBG_GAME_CONTEXT_H
#define RBG_GAME_CONTEXT_H

#include "rbg_player_context.h"
#include "rbg_input_context.h"
#include "rbg_scene_context.h"
#include "rbg_render_context.h"
#include <stdbool.h>
#include "raylib.h"

typedef struct RbgGameContext {
    bool game_initialized;

    // fixed timestep ctx
    double accumulator;
    double previous_time;
    double fixed_dt;
	double frame_time;
	int target_fps;

	int fps_display;
	int fps_count;
	double fps_timer;

	// cam ctx
	Camera2D camera;
	bool cam_initialized;

	// input ctx
	int current_recording_frame;
	bool is_recording_input;
	bool recording_buffer[MAX_RECORD_FRAMES][NUM_RECORD_ACTIONS];
	KeyboardKey input_bindings[INPUT_ACTION_COUNT];
	bool down_states[INPUT_ACTION_COUNT];
	bool pressed_states[INPUT_ACTION_COUNT];

	// player ctx
	rbg_player player_1;
	rbg_player player_2;
	
	rbg_player_col_box player_1_box;
	rbg_player_col_box player_2_box;

	// scene ctx
	bool scene_initialized;
	rbg_scene_type current_scene;
	rbg_scene_type next_scene;

	// sprite sheets (render) ctx
	SpriteSheet* spritesheets; // = NULL;
	int spritesheet_count; // = 0;
	sprite_sheet_animator sheet_animator_p1;
	sprite_sheet_animator sheet_animator_p2;
	
} RbgGameContext;

#endif
