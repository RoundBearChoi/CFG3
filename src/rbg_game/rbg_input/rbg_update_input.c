#include "rbg_update_input.h"
#include "raylib.h"

static bool input_initialized = false;

// Internal state updated every frame
static bool downStates[INPUT_ACTION_COUNT] = {false};
static bool pressedStates[INPUT_ACTION_COUNT] = {false};

KeyboardKey inputBindings[INPUT_ACTION_COUNT];

// String literals generated automatically by the X macro
static const char* const rbg_input_action_names[INPUT_ACTION_COUNT] = {
#define X(name) #name,
    RBG_INPUT_ACTIONS
#undef X
};

void rgb_init_input(void)
{
	// Default keyboard layout
    inputBindings[INPUT_P1_MOVE_LEFT]  = KEY_A;
    inputBindings[INPUT_P1_MOVE_RIGHT] = KEY_D;
    inputBindings[INPUT_P1_MOVE_UP]    = KEY_W;
    inputBindings[INPUT_P1_MOVE_DOWN]  = KEY_S;
    inputBindings[INPUT_P1_JUMP]       = KEY_R;
    inputBindings[INPUT_P1_ATTACK]     = KEY_T;
}

void rbg_update_input(void)
{
	// run once
	if (input_initialized == false)
	{
		input_initialized = true;
		rgb_init_input();
	}

	for (int i = 0; i < INPUT_ACTION_COUNT; i++)
    {
        downStates[i]    = IsKeyDown(inputBindings[i]);
        pressedStates[i] = IsKeyPressed(inputBindings[i]);
    }
}

bool IsInputActionDown(InputAction action)
{
    if (action < 0 || action >= INPUT_ACTION_COUNT) return false;

	return downStates[action];
}

bool IsInputActionPressed(InputAction action)
{
    if (action < 0 || action >= INPUT_ACTION_COUNT) return false;
    
	return pressedStates[action];
}

bool IsInputActionReleased(InputAction action)
{
    if (action < 0 || action >= INPUT_ACTION_COUNT) return false;
   
	// Simple released = was down last frame but not this frame
    return !downStates[action] && IsKeyUp(inputBindings[action]);
}
