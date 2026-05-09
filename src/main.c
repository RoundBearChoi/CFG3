#include "rbg_game/rbg_game.h"
#include "rbg_game/rbg_spritesheets/rbg_spritesheet_loader.h"
#include "raylib.h"
#include "math.h"

extern Camera2D rbg_global_camera;

int main(void)
{
    // fixed internal resolution
    const int virtualWidth  = 800;
    const int virtualHeight = 400;

    static const char* const bar_title = "C Fighting Game 3"; 

    InitWindow(virtualWidth, virtualHeight, bar_title);
    
    ClearWindowState(FLAG_VSYNC_HINT);
    SetTargetFPS(128);

    // create render target
    RenderTexture2D target = LoadRenderTexture(virtualWidth, virtualHeight);
    SetTextureFilter(target.texture, TEXTURE_FILTER_POINT);  // sharp pixels (no smoothing)

    // Track the original windowed size so we can restore it cleanly
    int windowedWidth  = virtualWidth;
    int windowedHeight = virtualHeight;

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_F11))
        {
            if (!IsWindowState(FLAG_BORDERLESS_WINDOWED_MODE))
            {
                // === ENTERING borderless fullscreen ===
                // 1. Remember current windowed size
                windowedWidth  = GetScreenWidth();
                windowedHeight = GetScreenHeight();

                // 2. Resize to monitor's native resolution FIRST
                int monitor = GetCurrentMonitor();
                SetWindowSize(GetMonitorWidth(monitor), GetMonitorHeight(monitor));

                // 3. Activate borderless windowed mode (no display-mode change)
                SetWindowState(FLAG_BORDERLESS_WINDOWED_MODE);
            }
            else
            {
                // === EXITING borderless fullscreen ===
                ClearWindowState(FLAG_BORDERLESS_WINDOWED_MODE);
                // Restore the saved windowed size
                SetWindowSize(windowedWidth, windowedHeight);
            }

            // Re-apply these after any window state change (GLFW can reset flags)
            ClearWindowState(FLAG_VSYNC_HINT);
            SetTargetFPS(128);
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
            (float)-target.texture.height   // negative height for OpenGL Y-flip
        };

        Rectangle dest = {
            (GetScreenWidth()  - (virtualWidth  * scale)) * 0.5f,
            (GetScreenHeight() - (virtualHeight * scale)) * 0.5f,
            virtualWidth  * scale,
            virtualHeight * scale
        };

        DrawTexturePro(target.texture, source, dest, (Vector2){0.0f, 0.0f}, 0.0f, WHITE);

        DrawFPS(10, 10);

        EndDrawing();
    }

    // Clean up
    UnloadRenderTexture(target);
    rbg_unload_sprite_sheets();
    CloseWindow();
    return 0;
}
