#include "rbg_game/rbg_game.h"
#include "rbg_game/rbg_spritesheets/rbg_spritesheet_loader.h"
#include "raylib.h"

extern Camera2D rbg_global_camera;

int main(void)
{
    const int screenWidth  = 1280;
    const int screenHeight = 720;

	// static = internal linkage. visible only inside the current file
	// const char* = string won't change
	// const = pointer won't change
	static const char* const bar_title = "C Fighting Game 3"; 

    // Initialize the window and OpenGL context
    InitWindow(screenWidth, screenHeight, bar_title);

    SetTargetFPS(60);

    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // All drawing must happen between BeginDrawing() and EndDrawing()
        BeginDrawing();
        ClearBackground(BLACK);

		// Camera mode - everything between here is in world coordinates
		BeginMode2D(rbg_global_camera);
		rbg_update_game();
		EndMode2D();
		
        DrawFPS(10, 10);

        EndDrawing();
    }

	// temp
	UnloadSpriteSheets();

    // Clean shutdown (always call this)
    CloseWindow();
    return 0;
}
