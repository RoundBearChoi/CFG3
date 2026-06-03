#include "rbg_sheet_animators.h"
#include "rbg_sheet_loader.h"
#include "../rbg_scenes/rbg_players/rbg_players.h"
#include "raylib.h"
#include <stddef.h>
#include <string.h>  // for memset

sprite_sheet_animator sheet_animator_p1;
sprite_sheet_animator sheet_animator_p2;

void rbg_init_sheet_animators()
{
	rbg_load_sprite_sheets("resources/fighters_spritesheet_list.csv");

	rbg_init_animator(&sheet_animator_p1, "fighter_0_idle", RENDER_PIVOT_BOTTOM_CENTER);
	rbg_init_animator(&sheet_animator_p2, "fighter_0_idle", RENDER_PIVOT_BOTTOM_CENTER);
}

void rbg_update_sheet_animators()
{
	sheet_animator_p1.is_facing_right_side = rbg_player_1.is_facing_right_side;
	sheet_animator_p2.is_facing_right_side = rbg_player_2.is_facing_right_side;

	rbg_update_animator(&sheet_animator_p1);
	rbg_update_animator(&sheet_animator_p2);

	TraceLog(LOG_INFO, "player 1 ani");
	rbg_draw_sprite_animation(&sheet_animator_p1, rbg_player_1.position, 1.0f, WHITE);
	TraceLog(LOG_INFO, "player 2 ani");
	rbg_draw_sprite_animation(&sheet_animator_p2, rbg_player_2.position , 1.0f, GRAY);
}

void rbg_change_player_animation(int playerIndex, const char* sheet_name)
{
	sprite_sheet_animator* animator = rbg_get_player_sheet_animator(playerIndex);

	if (animator != NULL)
	{
		animator->sheet = rbg_get_sprite_sheet_by_name(sheet_name);
		
		// start curr frame at 0 whenever new animation begins (otherwise player 1 and player 2 walk animations for example will sink)
		rbg_reset_animator(animator);
	}
}

sprite_sheet_animator* rbg_get_player_sheet_animator(int playerIndex)
{
	if (playerIndex == 1)
	{
		return &sheet_animator_p1;
	}
	else if (playerIndex == 2)
	{
		return &sheet_animator_p2;
	}
	return NULL;
}

void rbg_init_animator(sprite_sheet_animator* ani, const char* spritesheet_name, rbg_render_pivot pivot)
{
    if (ani == NULL) return;
    
	memset(ani, 0, sizeof(sprite_sheet_animator));
    
    ani->sheet = rbg_get_sprite_sheet_by_name(spritesheet_name);
    ani->pivot = pivot;
    ani->is_facing_right_side = true;  // default: right-facing (assuming all original png orientation is left to right)
    
    if (ani->sheet == NULL)
	{
        TraceLog(LOG_WARNING, "rbg_init_animator: Could not find spritesheet '%s'", spritesheet_name);
        return;
    }
    
    ani->is_playing = true;
    ani->loop = true;
}

void rbg_update_animator(sprite_sheet_animator* ani)
{
    if (ani == NULL || ani->sheet == NULL || !ani->is_playing) return;
    
    int delay = ani->sheet->play_delay > 0 ? ani->sheet->play_delay : 1;
    ani->frame_counter++;
    
    if (ani->frame_counter >= delay)
	{
        ani->frame_counter = 0;
        ani->current_frame = (ani->current_frame + 1) % ani->sheet->total_images;
        
        // One-shot handling: stop after one full cycle
        if (!ani->loop && ani->current_frame == 0)
		{
			//ani->is_playing = false;
        }
    }
}

void rbg_draw_sprite_animation(const sprite_sheet_animator* ani, Vector2 position, float extra_scale, Color tint)
{
    if (ani == NULL || ani->sheet == NULL || ani->sheet->texture.id == 0) return;
    
    SpriteSheet* s = ani->sheet;
    int frame = ani->current_frame;
   
	TraceLog(LOG_INFO, "drawing sprite ani frame %d", frame); 

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
    
	if (!ani->is_facing_right_side)
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
    switch (ani->pivot)
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
   

	TraceLog(LOG_INFO, "drawSource.x %d   width %d", drawSource.x, drawSource.width);
    DrawTexturePro(s->texture, drawSource, dest, origin, 0.0f, tint);
}

void rbg_reset_animator(sprite_sheet_animator* ani)
{
    if (ani == NULL) return;
    
	ani->current_frame = 0;
    ani->frame_counter = 0;
    ani->is_playing = true;  // most common after reset
    // loop, pivot, and is_facing_right_side are intentionally left unchanged
}
