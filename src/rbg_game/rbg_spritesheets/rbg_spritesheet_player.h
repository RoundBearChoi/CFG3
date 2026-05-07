#ifndef RBG_SPRITESHEET_PLAYER_H
#define RBG_SPRITESHEET_PLAYER_H

#include "rbg_spritesheet_loader.h"
#include "raylib.h"

typedef struct {
    Spritesheet* sheet;       // pointer to loaded data (do NOT free)
    int current_frame;        // 0 .. total_images-1
    int frame_counter;        // ticks until next frame
    bool is_playing;
    bool loop;                // false = one-shot animation
} SpriteSheetPlayer;

// Initialize player from fighter_type (looks up via loader)
void InitSpritesheetPlayer(SpriteSheetPlayer* player, const char* fighter_type);

// Advance animation (call every frame)
void UpdateSpritesheetPlayer(SpriteSheetPlayer* player);

// Draw the current frame (centered origin by default)
void DrawSpritesheetPlayer(const SpriteSheetPlayer* player, Vector2 position, float extra_scale, Color tint);

// Control playback
void PlaySpritesheet(SpriteSheetPlayer* player, bool loop);
void StopSpritesheet(SpriteSheetPlayer* player);
void ResetSpritesheetPlayer(SpriteSheetPlayer* player);

#endif
