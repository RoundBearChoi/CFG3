#include "rbg_cam_control.h"
#include "../rbg_scenes/rbg_input/rbg_update_input.h"
#include "raylib.h"

// Definition (no extern) – this is the real variable
Camera2D global_rbg_camera;

// specific to test_scene_2
void rbg_init_cam_control(void)
{
	global_rbg_camera.offset = (Vector2){ 0.0f, 0.0f };
	global_rbg_camera.target = (Vector2){ -600.0f, -600.0f }; // behaves like camera position
	global_rbg_camera.rotation = 0.0f;
	global_rbg_camera.zoom = 1.0f;
}

// specific to test_scene_2
void rbg_update_cam_control(void)
{

}
