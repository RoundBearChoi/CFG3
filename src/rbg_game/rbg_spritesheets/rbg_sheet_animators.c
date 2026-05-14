#include "rbg_sheet_animators.h"
#include "rbg_spritesheet_player.h"
#include "raylib.h"

SpriteSheetPlayer sheet_animator_p1;
SpriteSheetPlayer sheet_animator_p2;

void rbg_init_sheet_animators()
{
	rbg_init_sprite_sheet(&sheet_animator_p1, "fighter_0_idle", RENDER_PIVOT_BOTTOM_CENTER);

	rbg_init_sprite_sheet(&sheet_animator_p2, "fighter_0_idle", RENDER_PIVOT_BOTTOM_CENTER);
}

void rbg_update_sheet_animators()
{
	rbg_update_sprite_sheet(&sheet_animator_p1);
	rbg_update_sprite_sheet(&sheet_animator_p2);

	rbg_draw_sprite_sheet(&sheet_animator_p1, (Vector2){ 0.0f, 0.0f}, 1.0f, RED);
	rbg_draw_sprite_sheet(&sheet_animator_p2, (Vector2){ 20.0f, 0.0f} , 1.0f, BLUE);
}
