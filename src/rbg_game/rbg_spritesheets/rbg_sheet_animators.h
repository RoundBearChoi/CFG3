#ifndef RBG_SHEET_ANIMATORS_H
#define RBG_SHEET_ANIMATORS_H

#include "rbg_spritesheet_animator.h"

extern sprite_sheet_animation sheet_animator_p1;
extern sprite_sheet_animation sheet_animator_p2;

void rbg_init_sheet_animators();
void rbg_update_sheet_animators();
void rbg_change_player_animation(int playerIndex, const char* sheet_name);

#endif
