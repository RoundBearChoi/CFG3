#include "rbg_spritesheet_player.h"
#include <string.h>  // for memset

void InitSpritesheetPlayer(SpriteSheetPlayer* player, const char* fighter_type)
{
    if (player == NULL) return;
    memset(player, 0, sizeof(SpriteSheetPlayer));
    
    player->sheet = GetSpritesheet(fighter_type);
    player->is_playing = true;
    player->loop = true;
    
    // Defensive: if delay is invalid, treat as 1
    if (player->sheet && player->sheet->play_delay <= 0) {
        // We don't modify the original sheet, just clamp locally if needed
    }
}

void UpdateSpritesheetPlayer(SpriteSheetPlayer* player)
{
    if (player == NULL || player->sheet == NULL || !player->is_playing) return;
    
    int delay = player->sheet->play_delay > 0 ? player->sheet->play_delay : 1;
    player->frame_counter++;
    
    if (player->frame_counter >= delay) {
        player->frame_counter = 0;
        player->current_frame = (player->current_frame + 1) % player->sheet->total_images;
        
        // One-shot handling: stop after one full cycle
        if (!player->loop && player->current_frame == 0) {
            player->is_playing = false;
        }
    }
}

void DrawSpritesheetPlayer(const SpriteSheetPlayer* player, Vector2 position, float extra_scale, Color tint)
{
    if (player == NULL || player->sheet == NULL || player->sheet->texture.id == 0) return;
    
    Spritesheet* s = player->sheet;
    int frame = player->current_frame;
    
    // Calculate source rectangle (row-major order, respect total_images)
    Rectangle source = {
        (frame % s->total_x) * s->frame_width,
        (frame / s->total_x) * s->frame_height,
        (float)s->frame_width,
        (float)s->frame_height
    };
    
    // Destination rectangle (apply both CSV render_scale + runtime extra_scale)
    float final_scale = s->render_scale * extra_scale;
    Rectangle dest = {
        position.x,
        position.y,
        s->frame_width * final_scale,
        s->frame_height * final_scale
    };
    
    // Center origin (standard for character sprites)
    Vector2 origin = { dest.width / 2.0f, dest.height / 2.0f };
    
    DrawTexturePro(s->texture, source, dest, origin, 0.0f, tint);
}

void PlaySpritesheet(SpriteSheetPlayer* player, bool loop)
{
    if (player == NULL) return;
    player->is_playing = true;
    player->loop = loop;
    // Optional: reset frame when starting new playback
    // player->current_frame = 0;
}

void StopSpritesheet(SpriteSheetPlayer* player)
{
    if (player == NULL) return;
    player->is_playing = false;
}

void ResetSpritesheetPlayer(SpriteSheetPlayer* player)
{
    if (player == NULL) return;
    player->current_frame = 0;
    player->frame_counter = 0;
    player->is_playing = true;  // most common after reset
}
