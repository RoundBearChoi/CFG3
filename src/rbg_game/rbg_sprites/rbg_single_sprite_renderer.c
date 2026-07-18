#include "rbg_single_sprite_renderer.h"
#include "../rbg_sprites/rbg_single_sprite_loader.h"

void rbg_render_single_sprite(RbgGameContext* game_ctx, const char *sprite_name, Vector2 position, float scale, Color tint)
{
    single_sprite* sprite = rbg_get_single_sprite_by_name(game_ctx, sprite_name);
    
	if (sprite && sprite->texture.id != 0)
    {
        DrawTextureEx(sprite->texture, position, 0.0f, scale, tint);
    }
}
