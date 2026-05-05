#include "rbg_game.h"
#include "rbg_scenes/rbg_scenes.h"
#include "rbg_render_debug/rbg_render_debug.h"

void rbg_update_game(void)
{
	rbg_update_scenes();
	rbg_render_debug();
}
