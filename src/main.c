#include "raylib.h"
#include "rbg_render_debug/rbg_render_debug.h"

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

        // Clear the screen with a nice light background
        ClearBackground(RAYWHITE);

		RBG_RenderDebug();

        // Simple welcome text (centered-ish)
        DrawText("Congrats! You created your first raylib window in C!",
                 120, 180, 20, LIGHTGRAY);

        // ── Example shapes 
        // DrawRectangle(300, 300, 200, 150, RED);
        // DrawCircle(600, 300, 60, BLUE);
        // DrawLine(100, 100, 700, 400, GREEN);

        // Optional: show current FPS in top-left corner
        DrawFPS(10, 10);

        EndDrawing();
    }

    // Clean shutdown (always call this)
    CloseWindow();
    return 0;
}
