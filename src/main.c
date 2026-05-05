#include "raylib.h"
#include "rbg_game/rbg_game.h"

int main(void)
{
    const int screenWidth  = 800;
    const int screenHeight = 450;

    // Initialize the window and OpenGL context
    InitWindow(screenWidth, screenHeight, "C Fighting Game 3");

    SetTargetFPS(60);

    // ================================================
    // Main game loop
    // ================================================
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // All drawing must happen between BeginDrawing() and EndDrawing()
        BeginDrawing();

        ClearBackground(BLACK);

		rbg_update_game();
		
        DrawFPS(10, 10);

        EndDrawing();
    }

    // Clean shutdown (always call this)
    CloseWindow();
    return 0;
}
