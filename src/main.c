#include "rbg_game/rbg_game.h"
#include "rbg_game/rbg_render_on_screenspace.h"
#include "rbg_game/rbg_spritesheets/rbg_sheet_loader.h"
#include "raylib.h"
#include "math.h"
#include <stddef.h>

extern Camera2D rbg_global_camera;
extern int rbg_target_fps;
extern Font press_start;

int main(void)
{
    // fixed internal resolution
    const int virtualWidth  = 800;
    const int virtualHeight = 400;

    // integer scale windowed modes (perfect pixel scaling)
    const int scale2Width   = virtualWidth * 2;  // 1600
    const int scale2Height  = virtualHeight * 2; // 800
    const int scale3Width   = virtualWidth * 3;  // 2400
    const int scale3Height  = virtualHeight * 3; // 1200

	// 0 = 1x (800x400), 1 = 2x (1600x800), 2 = 3x (2400x1200), 3 = fullscreen
	int window_mode = 1;

	static const char* const bar_title = "C Fighting Game 3"; 

	InitWindow(virtualWidth, virtualHeight, bar_title);
    ClearWindowState(FLAG_VSYNC_HINT);
    SetTargetFPS(rbg_target_fps);

	// font
	press_start = LoadFontEx("PrStart.ttf", 32, NULL, 0);
	SetTextureFilter(press_start.texture, TEXTURE_FILTER_POINT);
    
	// create render target
    RenderTexture2D target = LoadRenderTexture(virtualWidth, virtualHeight);
    SetTextureFilter(target.texture, TEXTURE_FILTER_POINT);  // sharp pixels (no smoothing)

    while (!WindowShouldClose())
    {
		static bool first_frame = true;

        if (IsKeyPressed(KEY_F11) || first_frame == true)
        {
			if (first_frame == true) window_mode -= 1;
			first_frame = false;
			
            window_mode = (window_mode + 1) % 4;

            if (window_mode == 3)  // === entering exclusive fullscreen ===
            {
                // resize to monitor's native resolution first
                int monitor = GetCurrentMonitor();
                SetWindowSize(GetMonitorWidth(monitor), GetMonitorHeight(monitor));

                // go true fullscreen
                ToggleFullscreen();
            }
            else  // === windowed mode 0, 1 or 2 ===
            {
                // if we were in fullscreen, exit it first
                if (IsWindowFullscreen())
                {
                    ToggleFullscreen();
                }

                // set target window size for the chosen mode
                int targetW = 800;
				int targetH= 400;
                switch(window_mode)
                {
                    case 0:
                        targetW = virtualWidth;
                        targetH = virtualHeight;
                        break;
                    case 1:
                        targetW = scale2Width;
                        targetH = scale2Height;
                        break;
                    case 2:
                        targetW = scale3Width;
                        targetH = scale3Height;
                        break;
                }

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
	UnloadFont(press_start);
    CloseWindow();
    return 0;
}
