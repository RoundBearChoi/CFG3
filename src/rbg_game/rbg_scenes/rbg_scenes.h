#ifndef RBG_SCENES_H
#define RBG_SCENES_H

void rbg_update_scenes(void);

typedef enum {
    TEST_SCENE_1,
    TEST_SCENE_2,
    NUM_SCENES
} rbg_scene_type;

extern rbg_scene_type current_scene;

// Function pointer type for scene updates
typedef void (*SceneUpdateFn)(void);

#endif
