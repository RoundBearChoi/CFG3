#include "rbg_game_context.h"
#include "raylib.h"
#include <stddef.h>

RbgGameContext create_default_game_ctx(void)
{
    RbgGameContext game_ctx = {
        .game_initialized = false,
		
		.accumulator = 0.0,
		.previous_time = 0.0,
        .frame_time = 0,
		.fixed_dt = 1.0 / 128.0,
		.target_fps = 128,
		
		.fps_display = 0,
		.fps_count = 0,
		.fps_timer = 0,
        
		.current_scene = TEST_SCENE_2, // starting scene
		.next_scene = NO_SCENE,

        .scene_initialized = false,
        .sprite_sheets = NULL,
        .sprite_sheet_count = 0,

        .camera = {
            .zoom = 1.0f,
            .rotation = 0.0f,
            .target = (Vector2){ -600.0f, -600.0f },
            .offset = (Vector2){ 0.0f, 0.0f }
        }
    };

    return game_ctx;
}
