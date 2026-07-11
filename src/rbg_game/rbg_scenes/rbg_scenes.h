#ifndef RBG_SCENES_H
#define RBG_SCENES_H

#include "../rbg_game_context.h"

void rbg_init_scenes(RbgGameContext* ctx);
void rbg_update_scenes(RbgGameContext* ctx);
void rbg_render_scenes(RbgGameContext* ctx);
void rbg_set_next_scene(RbgGameContext* ctx, rbg_scene_type next_scene);

// Function pointer types for scene dispatch (update & render)
typedef void (*SceneUpdateFn)(RbgGameContext* ctx);
typedef void (*SceneRenderFn)(RbgGameContext* ctx);

#endif
