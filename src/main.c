#include "rbg_game/rbg_game.h"
#include "rbg_game/rbg_render_on_screenspace.h"
#include "rbg_game/rbg_spritesheets/rbg_sheet_loader.h"
#include "raylib.h"
#include "math.h"
#include <stddef.h>

//extern int global_rbg_target_fps;
extern Font global_font_press_start;

int main(void)
{
    const int virtualWidth  = 1600;
    const int virtualHeight = 800;

    // windowed modes - integer scale (perfect pixel scaling)
    const int nativeWidth   = 1600;   // 1× virtual
    const int nativeHeight  = 800;
    const int highWidth     = 2400;   // 1.5× virtual (still crisp with POINT filter)
    const int highHeight    = 1200;

	static const char* const bar_title = "C Fighting Game 3"; 

	// game context instance
	RbgGameContext game_ctx = {0};
	game_ctx.target_fps = 128;

	// start at native resolution (1600x800)
	InitWindow(nativeWidth, nativeHeight, bar_title);
    ClearWindowState(FLAG_VSYNC_HINT);
    SetTargetFPS(game_ctx.target_fps);

	// font
	global_font_press_start = LoadFontEx("PrStart.ttf", 32, NULL, 0);
	SetTextureFilter(global_font_press_start.texture, TEXTURE_FILTER_POINT);
    
	// create render target (native resolution)
    RenderTexture2D target = LoadRenderTexture(virtualWidth, virtualHeight);
    SetTextureFilter(target.texture, TEXTURE_FILTER_POINT);  // sharp pixels (no smoothing)

	// 0 = native 1600x800 (default), 1 = 2400x1200, 2 = fullscreen
	int window_mode = 0;

	while (!WindowShouldClose())
    {
        // cycle window modes with F11
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
                // if fullscreen, exit first
                if (IsWindowFullscreen())
                {
                    ToggleFullscreen();
                }

                // set target window size for chosen mode
                int targetW = nativeWidth;
                int targetH = nativeHeight;
                if (window_mode == 1)
                {
                    targetW = highWidth;
                    targetH = highHeight;
                }

                SetWindowSize(targetW, targetH);
            }

            // re-apply after window change
            ClearWindowState(FLAG_VSYNC_HINT);
            SetTargetFPS(game_ctx.target_fps);
        }

        BeginDrawing();
        ClearBackground(BLACK);

        // draw everything to fixed render target
        BeginTextureMode(target);
            ClearBackground(BLACK);
            
            BeginMode2D(game_ctx.camera);
                rbg_run_game(&game_ctx); // (update + drawing)
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

		rbg_render_on_screenspace(&game_ctx);

        EndDrawing();
    }

    // clean up
    UnloadRenderTexture(target);
    rbg_unload_sprite_sheets(&game_ctx);
	UnloadFont(global_font_press_start);
    CloseWindow();
    return 0;
}
