#include "raylib.h"
#include "rbg_render_debug/rbg_render_debug.h"
#include "rbg_game/rbg_game.h"

int main(void)
{
    // ================================================
    // Window configuration
    // ================================================
    const int screenWidth  = 800;
    const int screenHeight = 450;

    // Initialize the window and OpenGL context
    InitWindow(screenWidth, screenHeight, "C Fighting Game 3");

    // Set target frame rate
    SetTargetFPS(60);

    // ================================================
    // Main game loop
    // ================================================
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // ── All drawing must happen between BeginDrawing() and EndDrawing()
        BeginDrawing();

        ClearBackground(BLACK);

		rbg_render_debug();
		rbg_update_game();

        DrawText("Congrats! You created your first raylib window in C!",
                 120, 180, 20, LIGHTGRAY);

        DrawFPS(10, 10);

        EndDrawing();
    }

    // Clean shutdown (always call this)
    CloseWindow();
    return 0;
}
