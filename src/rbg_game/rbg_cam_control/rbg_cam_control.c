#include "rbg_cam_control.h"
#include "raylib.h"

// Definition (no extern) – this is the real variable
Camera2D rbg_camera;

void rbg_update_cam_control(void)
{
    rbg_camera.offset   = (Vector2){ 100, 100 };
    rbg_camera.rotation = 0.0f;
    rbg_camera.zoom     = 1.0f;
}
