#include "rbg_spritesheet_player.h"
#include <string.h>  // for memset

void InitSpriteSheetPlayer(SpriteSheetPlayer* player, const char* spritesheet_name)
{
    if (player == NULL) return;
    memset(player, 0, sizeof(SpriteSheetPlayer));
    
    player->sheet = GetSpriteSheetByName(spritesheet_name);
    
    if (player->sheet == NULL) {
        TraceLog(LOG_WARNING, "InitSpriteSheetPlayer: Could not find spritesheet '%s'", spritesheet_name);
        return;
    }
    
    player->is_playing = true;
    player->loop = true;
    
    TraceLog(LOG_INFO, "Initialized SpriteSheetPlayer for '%s' (%d frames)", 
             spritesheet_name, player->sheet->total_images);
}

void UpdateSpriteSheetPlayer(SpriteSheetPlayer* player)
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

void DrawSpriteSheetPlayer(const SpriteSheetPlayer* player, Vector2 position, float extra_scale, Color tint)
{
    if (player == NULL || player->sheet == NULL || player->sheet->texture.id == 0) return;
    
    SpriteSheet* s = player->sheet;
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

void PlaySpriteSheet(SpriteSheetPlayer* player, bool loop)
{
    if (player == NULL) return;
    player->is_playing = true;
    player->loop = loop;
}

void StopSpriteSheet(SpriteSheetPlayer* player)
{
    if (player == NULL) return;
    player->is_playing = false;
}

void ResetSpriteSheetPlayer(SpriteSheetPlayer* player)
{
    if (player == NULL) return;
    player->current_frame = 0;
    player->frame_counter = 0;
    player->is_playing = true;  // most common after reset
}
