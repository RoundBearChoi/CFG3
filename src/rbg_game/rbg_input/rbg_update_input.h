#ifndef RBG_UPDATE_INPUT_H
#define RBG_UPDATE_INPUT_H

#include "raylib.h"

typedef enum {
    INPUT_P1_MOVE_LEFT,
    INPUT_P1_MOVE_RIGHT,
    INPUT_P1_MOVE_UP,
    INPUT_P1_MOVE_DOWN,
    INPUT_P1_JUMP,
    INPUT_P1_ATTACK,


    INPUT_ACTION_COUNT
} InputAction;

// extern = “This exists somewhere else (in another .c file).
//          I’m only declaring it here so other files can see it and use it.
//          Do not create a new copy of this.”
extern KeyboardKey inputBindings[INPUT_ACTION_COUNT];

void rbg_init_input(void);
void rbg_update_input(void);

// Query functions
bool IsInputActionDown(InputAction action); // key is held down right now (continuous)
bool IsInputActionPressed(InputAction action); // key was pressed this exact frame
bool IsInputActionReleased(InputAction action);

#endif
