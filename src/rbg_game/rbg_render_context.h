#ifndef RBG_RENDER_CONTEXT_H
#define RBG_RENDER_CONTEXT_H

// Enum that controls where the 'position' parameter points to in rbg_draw_sprite_animation.
// CENTER is the original behavior; BOTTOM_CENTER is useful for characters standing on the ground.
typedef enum rbg_render_pivot {
    RENDER_PIVOT_CENTER,
    RENDER_PIVOT_BOTTOM_CENTER
} rbg_render_pivot;

typedef struct sprite_sheet {
    char *fighter_type;
    char *sprite_sheet_name; // base name WITHOUT .png (automatically cleaned from CSV)
    int total_x;
    int total_y;
    int total_images;
    float render_scale;
    int play_delay;

    Texture2D texture;      // loaded by Raylib
    int frame_width;        // pre-computed: texture.width / total_x
    int frame_height;       // pre-computed: texture.height / total_y
} sprite_sheet;

typedef struct sprite_sheet_animator {
    sprite_sheet* sheet;       // pointer to loaded data (do NOT free)
    int current_frame;
    int frame_counter;        // ticks until next frame
    bool is_playing;
    rbg_render_pivot pivot;
    bool is_facing_right_side; // true = original PNG right-facing orientation (default)
                               // false = horizontal mirror flip (left-facing)
} sprite_sheet_animator;

#endif
