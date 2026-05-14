#ifndef RBG_SPRITESHEET_PLAYER_H
#define RBG_SPRITESHEET_PLAYER_H

#include "rbg_spritesheet_loader.h"
#include "raylib.h"

// Enum that controls where the 'position' parameter points to in rbg_draw_sprite_sheet.
// CENTER is the original behavior; BOTTOM_CENTER is useful for characters standing on the ground.
typedef enum
{
    RENDER_PIVOT_CENTER,
    RENDER_PIVOT_BOTTOM_CENTER
} rbg_render_pivot;

typedef struct
{
    SpriteSheet* sheet;       // pointer to loaded data (do NOT free)
    int current_frame;        // 0 .. total_images-1
    int frame_counter;        // ticks until next frame
    bool is_playing;
    bool loop;                // false = one-shot animation
    rbg_render_pivot pivot;
    bool is_facing_right_side; // true = original PNG right-facing orientation (default)
                               // false = horizontal mirror flip (left-facing)
} sprite_sheet_animation;

void rbg_init_sprite_sheet(sprite_sheet_animation* player, const char* spritesheet_name, rbg_render_pivot pivot); // Initialize player from spritesheet_name (looks up via rbg_get_sprite_sheet_by_name)
void rbg_update_sprite_sheet(sprite_sheet_animation* player); // Advance animation (call every frame)
void rbg_draw_sprite_sheet(const sprite_sheet_animation* player, Vector2 position, float extra_scale, Color tint);
void rbg_reset_sprite_sheet(sprite_sheet_animation* player);

#endif
