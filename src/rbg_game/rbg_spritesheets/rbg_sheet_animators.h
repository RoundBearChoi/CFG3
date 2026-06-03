#ifndef RBG_SHEET_ANIMATORS_H
#define RBG_SHEET_ANIMATORS_H

#include "rbg_sheet_loader.h"
#include "raylib.h"

// Enum that controls where the 'position' parameter points to in rbg_draw_sprite_animation.
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
    //bool loop;                // false = one-shot animation
    rbg_render_pivot pivot;
    bool is_facing_right_side; // true = original PNG right-facing orientation (default)
                               // false = horizontal mirror flip (left-facing)
} sprite_sheet_animator;

extern sprite_sheet_animator sheet_animator_p1;
extern sprite_sheet_animator sheet_animator_p2;

void rbg_init_sheet_animators();
void rbg_update_sheet_animators();
void rbg_change_player_animation(int playerIndex, const char* sheet_name);
sprite_sheet_animator* rbg_get_player_sheet_animator(int playerIndex);
void rbg_init_animator(sprite_sheet_animator* ani, const char* spritesheet_name, rbg_render_pivot pivot);
void rbg_update_animator(sprite_sheet_animator* ani); // Advance animation (call every frame)
void rbg_draw_sprite_animation(const sprite_sheet_animator* ani, Vector2 position, float extra_scale, Color tint);
void rbg_reset_animator(sprite_sheet_animator* ani);

#endif
