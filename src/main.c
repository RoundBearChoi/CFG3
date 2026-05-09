#include "rbg_game/rbg_game.h"
#include "rbg_game/rbg_render_on_screenspace.h"
#include "rbg_game/rbg_spritesheets/rbg_spritesheet_loader.h"
#include "raylib.h"
#include "math.h"

extern Camera2D rbg_global_camera;
extern int rbg_target_fps;

int main(void)
{
    // fixed internal resolution
    const int virtualWidth  = 800;
    const int virtualHeight = 400;

    // double-size windowed mode (perfect integer upscale)
    const int scale2Width   = virtualWidth * 2; // 1600
    const int scale2Height  = virtualHeight * 2; // 800

    // current display mode (cycles on every F11 press)
    int window_mode = 0; // 0 = original 800x400, 1 = double 1600x800, 2 = fullscreen

    static const char* const bar_title = "C Fighting Game 3"; 
    InitWindow(virtualWidth, virtualHeight, bar_title);
    ClearWindowState(FLAG_VSYNC_HINT);
    SetTargetFPS(rbg_target_fps);

    // create render target
    RenderTexture2D target = LoadRenderTexture(virtualWidth, virtualHeight);
    SetTextureFilter(target.texture, TEXTURE_FILTER_POINT);  // sharp pixels (no smoothing)

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_F11))
        {
            window_mode = (window_mode + 1) % 3;

            if (window_mode == 2)  // === entering exclusive fullscreen ===
            {
                // resize to monitor's native resolution first
                int monitor = GetCurrentMonitor();
                SetWindowSize(GetMonitorWidth(monitor), GetMonitorHeight(monitor));

                // go true fullscreen
                ToggleFullscreen();
            }
            else  // === windowed mode 0 or 1 ===
            {
                // if we were in fullscreen, exit it first
                if (IsWindowFullscreen())
                {
                    ToggleFullscreen();
                }

                // set target window size for the chosen mode
                int targetW = (window_mode == 0) ? virtualWidth  : scale2Width;
                int targetH = (window_mode == 0) ? virtualHeight : scale2Height;

                SetWindowSize(targetW, targetH);
            }

            // re-apply after any window state change
            ClearWindowState(FLAG_VSYNC_HINT);
            SetTargetFPS(rbg_target_fps);
        }

        BeginDrawing();
        ClearBackground(BLACK);

        // draw everything to fixed render target
        BeginTextureMode(target);
            ClearBackground(BLACK);
            
            BeginMode2D(rbg_global_camera);
                rbg_update_game(); // (update + drawing)
            EndMode2D();
        EndTextureMode();

        // scale render target to the actual screen/window size
        float scale = fminf(
            (float)GetScreenWidth()  / (float)virtualWidth,
            (float)GetScreenHeight() / (float)virtualHeight
        );

        Rectangle source = {
            0.0f, 
            0.0f, 
            (float)target.texture.width, 
            (float)-target.texture.height // negative height for OpenGL Y-flip
        };

        Rectangle dest = {
            (GetScreenWidth()  - (virtualWidth  * scale)) * 0.5f,
            (GetScreenHeight() - (virtualHeight * scale)) * 0.5f,
            virtualWidth  * scale,
            virtualHeight * scale
        };

        DrawTexturePro(target.texture, source, dest, (Vector2){0.0f, 0.0f}, 0.0f, WHITE);

		rbg_render_on_screenspace();

        EndDrawing();
    }

    // clean up
    UnloadRenderTexture(target);
    rbg_unload_sprite_sheets();
    CloseWindow();
    return 0;
}
