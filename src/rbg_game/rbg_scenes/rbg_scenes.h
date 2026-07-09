#ifndef RBG_SCENES_H
#define RBG_SCENES_H

#include "../rbg_game_context.h"

void rbg_update_scenes(RbgGameContext* ctx);
void rbg_render_scenes(RbgGameContext* ctx);

typedef enum
{
	NONE = -1,
    TEST_SCENE_1,
    TEST_SCENE_2,
    NUM_SCENES
} rbg_scene_type;

void rbg_set_next_scene(rbg_scene_type next_scene);

// Function pointer types for scene dispatch (update & render)
typedef void (*SceneUpdateFn)(RbgGameContext* ctx);
typedef void (*SceneRenderFn)(RbgGameContext* ctx);

#endif
