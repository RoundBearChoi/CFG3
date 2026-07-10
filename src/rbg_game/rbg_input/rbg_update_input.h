#ifndef RBG_UPDATE_INPUT_H
#define RBG_UPDATE_INPUT_H

#include "../rbg_game_context.h"
#include "raylib.h"

// extern = “This exists somewhere else (in another .c file).
//          I’m only declaring it here so other files can see it and use it.
//          Do not create a new copy of this.”
extern KeyboardKey inputBindings[INPUT_ACTION_COUNT];

extern const char* const rbg_input_action_names[INPUT_ACTION_COUNT];

bool rbg_load_default_key_bindings(void);
void rbg_init_input(RbgGameContext *game_ctx);
void rbg_update_input(RbgGameContext *game_ctx);
InputAction rbg_get_move_left(int playerIndex);
InputAction rbg_get_move_right(int playerIndex);
InputAction rbg_get_move_up(int playerIndex);

// query functions
bool IsInputActionDown(InputAction action); // key is held down right now (continuous)
bool IsInputActionPressed(InputAction action); // key was pressed this exact frame
bool IsInputActionReleased(InputAction action);

#endif
