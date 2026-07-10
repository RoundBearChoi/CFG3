#ifndef RBG_UPDATE_INPUT_H
#define RBG_UPDATE_INPUT_H

#include "../rbg_game_context.h"
#include "raylib.h"

// ============================================================
//  SINGLE SOURCE OF TRUTH
//  Enum name and string literal sit side-by-side → easy to compare
// ============================================================
#define RBG_INPUT_ACTIONS \
    X(INPUT_P1,               "INPUT_P1") \
    X(INPUT_P1_MOVE_LEFT,     "INPUT_P1_MOVE_LEFT") \
    X(INPUT_P1_MOVE_RIGHT,    "INPUT_P1_MOVE_RIGHT") \
    X(INPUT_P1_MOVE_UP,       "INPUT_P1_MOVE_UP") \
    X(INPUT_P1_MOVE_DOWN,     "INPUT_P1_MOVE_DOWN") \
    X(INPUT_P1_JUMP,          "INPUT_P1_JUMP") \
    X(INPUT_P1_ATTACK,        "INPUT_P1_ATTACK") \
    \
    X(INPUT_P2,               "INPUT_P2") \
    X(INPUT_P2_MOVE_LEFT,     "INPUT_P2_MOVE_LEFT") \
    X(INPUT_P2_MOVE_RIGHT,    "INPUT_P2_MOVE_RIGHT") \
    X(INPUT_P2_MOVE_UP,       "INPUT_P2_MOVE_UP") \
    X(INPUT_P2_MOVE_DOWN,     "INPUT_P2_MOVE_DOWN") \
    X(INPUT_P2_JUMP,          "INPUT_P2_JUMP") \
    X(INPUT_P2_ATTACK,        "INPUT_P2_ATTACK") \
    \
    X(INPUT_F1,               "INPUT_F1") \
    X(INPUT_F2,               "INPUT_F2") \
    X(INPUT_F3,               "INPUT_F3") \
    \
    X(END_OF_INPUT,           "END_OF_INPUT")

// ---- Generate the enum ----
typedef enum
{
#define X(id, str) id,
    RBG_INPUT_ACTIONS
#undef X
    INPUT_ACTION_COUNT
} InputAction;

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
