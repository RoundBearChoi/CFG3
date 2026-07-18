#include "rbg_single_sprite_renderer.h"
#include "../rbg_sprites/rbg_single_sprite_loader.h"

void rbg_render_single_sprite(RbgGameContext* game_ctx, const char *sprite_name, Vector2 position, float scale, rbg_render_pivot pivot, Color tint)
{
    single_sprite* sprite = rbg_get_single_sprite_by_name(game_ctx, sprite_name);

    if (sprite && sprite->texture.id != 0)
    {
        Texture2D tex = sprite->texture;

        float width  = (float)tex.width  * scale;
        float height = (float)tex.height * scale;

        Rectangle source = {
            0.0f,
            0.0f,
            (float)tex.width,
            (float)tex.height
        };

        Rectangle dest = {
            position.x,
            position.y,
            width,
            height
        };

        // Same pivot logic you already use in rbg_draw_sprite_animation
        Vector2 origin;
        switch (pivot)
        {
            case RENDER_PIVOT_CENTER:
                origin = (Vector2){ width * 0.5f, height * 0.5f };
                break;

            case RENDER_PIVOT_BOTTOM_CENTER:
                origin = (Vector2){ width * 0.5f, height };          // bottom edge
                break;

            default:
                origin = (Vector2){ width * 0.5f, height * 0.5f };
                break;
        }

        DrawTexturePro(tex, source, dest, origin, 0.0f, tint);
    }
}
