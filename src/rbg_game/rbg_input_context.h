#ifndef RBG_INPUT_CONTEXT_H
#define RBG_INPUT_CONTEXT_H

// this is the single source of truth
// both InputAction enum and input_action_names[] table are generated from this list (side-by-side for easy comparison)

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

typedef enum
{
#define X(id, str) id,
    RBG_INPUT_ACTIONS
#undef X
    INPUT_ACTION_COUNT
} InputAction;

#define MAX_RECORD_FRAMES    (45 * 128) // 5760 frames (45 seconds @ 128 FPS)
#define RECORD_FIRST_ACTION  INPUT_P1
#define RECORD_LAST_ACTION   END_OF_INPUT
#define NUM_RECORD_ACTIONS   ((int)(RECORD_LAST_ACTION - RECORD_FIRST_ACTION + 1))

#endif
