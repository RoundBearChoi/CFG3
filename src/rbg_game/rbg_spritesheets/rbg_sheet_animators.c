#include "rbg_sheet_animators.h"
#include "rbg_spritesheet_loader.h"
#include "rbg_sheet_updater.h"
#include "../rbg_scenes/rbg_players/rbg_players.h"
#include "raylib.h"
#include <stddef.h>

sprite_sheet_animation sheet_animator_p1;
sprite_sheet_animation sheet_animator_p2;

void rbg_init_sheet_animators()
{
	rbg_load_sprite_sheets("resources/fighters_spritesheet_list.csv");

	rbg_init_sprite_sheet(&sheet_animator_p1, "fighter_0_idle", RENDER_PIVOT_BOTTOM_CENTER);
	rbg_init_sprite_sheet(&sheet_animator_p2, "fighter_0_idle", RENDER_PIVOT_BOTTOM_CENTER);
}

void rbg_update_sheet_animators()
{
	rbg_update_sprite_sheet(&sheet_animator_p1);
	rbg_update_sprite_sheet(&sheet_animator_p2);

	rbg_draw_sprite_sheet(&sheet_animator_p1, rbg_player_1.position, 1.0f, WHITE);
	rbg_draw_sprite_sheet(&sheet_animator_p2, rbg_player_2.position , 1.0f, GRAY);
}

void rbg_change_player_animation(int playerIndex, const char* sheet_name)
{
	sprite_sheet_animation* animator = NULL;

	if (playerIndex == 1)
	{
		animator = &sheet_animator_p1;
	}
	else if (playerIndex == 2)
	{
		animator = &sheet_animator_p2;
	}

	if (animator != NULL)
	{
		animator->sheet = rbg_get_sprite_sheet_by_name(sheet_name);
	}
}
