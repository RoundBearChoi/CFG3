#include "rbg_game_context.h"
#include "raylib.h"
#include <stddef.h>

RbgGameContext create_default_game_ctx(void)
{
    RbgGameContext ctx = {
        .game_initialized = false,
		
		.accumulator = 0.0,
		.previous_time = 0.0,
		.target_fps = 128,
        .fixed_dt = 1.0 / 128.0,
		
		.fps_count = 0,
		.fps_display = 0,
		.fps_timer = 0,
        
		.current_scene = TEST_SCENE_2,
		.next_scene = NONE,

        .cam_initialized = false,
        .scene_initialized = false,
        .spritesheets = NULL,
        .spritesheet_count = 0,

        // Camera2D defaults (important for Raylib)
        .camera = {
            .zoom = 1.0f,
            .rotation = 0.0f,
            .target = { -600.0f, -600.0f },
            .offset = (Vector2){ 0.0f, 0.0f }
        }
    };

    return ctx;
}
