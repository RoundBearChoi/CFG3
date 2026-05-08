#include "rbg_spritesheet_player.h"
#include <string.h>  // for memset

void rbg_init_sprite_sheet(SpriteSheetPlayer* player, const char* spritesheet_name, rbg_render_pivot pivot)
{
    if (player == NULL) return;
    
	memset(player, 0, sizeof(SpriteSheetPlayer));
    
    player->sheet = rbg_get_sprite_sheet_by_name(spritesheet_name);
    player->pivot = pivot;
    player->is_facing_right_side = true;  // default: right-facing (assuming all original png orientation is left to right)
    
    if (player->sheet == NULL)
	{
        TraceLog(LOG_WARNING, "rbg_init_sprite_sheet: Could not find spritesheet '%s'", spritesheet_name);
        return;
    }
    
    player->is_playing = true;
    player->loop = true;
}

void rbg_update_sprite_sheet(SpriteSheetPlayer* player)
{
    if (player == NULL || player->sheet == NULL || !player->is_playing) return;
    
    int delay = player->sheet->play_delay > 0 ? player->sheet->play_delay : 1;
    player->frame_counter++;
    
    if (player->frame_counter >= delay)
	{
        player->frame_counter = 0;
        player->current_frame = (player->current_frame + 1) % player->sheet->total_images;
        
        // One-shot handling: stop after one full cycle
        if (!player->loop && player->current_frame == 0)
		{
            player->is_playing = false;
        }
    }
}

void rbg_draw_sprite_sheet(const SpriteSheetPlayer* player, Vector2 position, float extra_scale, Color tint)
{
    if (player == NULL || player->sheet == NULL || player->sheet->texture.id == 0) return;
    
    SpriteSheet* s = player->sheet;
    int frame = player->current_frame;
    
    // Calculate source rectangle (row-major order, respect total_images)
    Rectangle source =
	{
        (frame % s->total_x) * s->frame_width,
        (frame / s->total_x) * s->frame_height,
        (float)s->frame_width,
        (float)s->frame_height
    };
    
    // Horizontal mirror flip when not facing right
    Rectangle drawSource = source;
    
	if (!player->is_facing_right_side)
	{
        drawSource.x += (float)s->frame_width;
        drawSource.width = -(float)s->frame_width;
    }
    
    // Destination rectangle (apply both CSV render_scale + runtime extra_scale)
    float final_scale = s->render_scale * extra_scale;
    float fw = s->frame_width * final_scale;
    float fh = s->frame_height * final_scale;
    
    Rectangle dest =
	{
        position.x,
        position.y,
        fw,
        fh
    };
    
    // Pivot-based origin (works correctly with flip)
    Vector2 origin;
    switch (player->pivot)
	{
        case RENDER_PIVOT_CENTER:
            origin = (Vector2){ fw * 0.5f, fh * 0.5f };
            break;
        case RENDER_PIVOT_BOTTOM_CENTER:
            origin = (Vector2){ fw * 0.5f, fh  };           // bottom edge
            break;
        default:
            origin = (Vector2){ fw * 0.5f, fh * 0.5f };
            break;
    }
    
    DrawTexturePro(s->texture, drawSource, dest, origin, 0.0f, tint);
}

void rbg_reset_sprite_sheet(SpriteSheetPlayer* player)
{
    if (player == NULL) return;
    
	player->current_frame = 0;
    player->frame_counter = 0;
    player->is_playing = true;  // most common after reset
    // loop, pivot, and is_facing_right_side are intentionally left unchanged
}
