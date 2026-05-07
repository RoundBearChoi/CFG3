#ifndef RBG_UPDATE_INPUT_H
#define RBG_UPDATE_INPUT_H

#include "raylib.h"

// X macro – single source of truth for all input enums
#define RBG_INPUT_ACTIONS \
    X(INPUT_P1_MOVE_LEFT)  \
    X(INPUT_P1_MOVE_RIGHT) \
    X(INPUT_P1_MOVE_UP)    \
    X(INPUT_P1_MOVE_DOWN)  \
    X(INPUT_P1_JUMP)       \
    X(INPUT_P1_ATTACK)

typedef enum {
#define X(name) name,
    RBG_INPUT_ACTIONS
#undef X
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
