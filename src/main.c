#include "rbg_game/rbg_game.h"
#include "raylib.h"

// Global camera
extern Camera2D rbg_camera;

int main(void)
{
    const int screenWidth  = 800;
    const int screenHeight = 450;

    // Initialize the window and OpenGL context
    InitWindow(screenWidth, screenHeight, "C Fighting Game 3");

    SetTargetFPS(60);

    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // All drawing must happen between BeginDrawing() and EndDrawing()
        BeginDrawing();
        ClearBackground(BLACK);

		// Camera mode - everything between here is in world coordinates
		BeginMode2D(rbg_camera);
		rbg_update_game();
		EndMode2D();
		
        DrawFPS(10, 10);

        EndDrawing();
    }

    // Clean shutdown (always call this)
    CloseWindow();
    return 0;
}
