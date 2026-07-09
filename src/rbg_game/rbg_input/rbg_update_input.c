#include "rbg_update_input.h"
#include "../../cJSON/cJSON.h"
#include "raylib.h"
#include <string.h>   // strcasecmp
#include <stdlib.h>   // atoi
#include <stdio.h>

// internal state updated every frame
static bool downStates[INPUT_ACTION_COUNT] = {false};
static bool pressedStates[INPUT_ACTION_COUNT] = {false};

KeyboardKey inputBindings[INPUT_ACTION_COUNT];

// string literals generated automatically by the X macro
// this is for converting enum to string literal or vice versa
const char* const rbg_input_action_names[INPUT_ACTION_COUNT] =
{
#define X(name) #name,
    RBG_INPUT_ACTIONS
#undef X
};

// key parser (supports F1-F12, space, arrows, modifiers, etc.)
static KeyboardKey string_to_keyboard_key(const char* keystr)
{
    if (keystr == NULL || keystr[0] == '\0')
	{
        return KEY_NULL;
    }

    // Backward-compatible single letters (a-z / A-Z)
    if (strlen(keystr) == 1)
	{
        char c = keystr[0];
        if ((c >= 'a' && c <= 'z'))
		{
            return (KeyboardKey)(KEY_A + (c - 'a'));
        }
        if ((c >= 'A' && c <= 'Z'))
		{
            return (KeyboardKey)(KEY_A + (c - 'A'));
        }
    }

    // F1–F12 (case-insensitive: "f1", "F1", "F12", etc.)
    if ((keystr[0] == 'F' || keystr[0] == 'f') && strlen(keystr) >= 2)
	{
        int num = atoi(keystr + 1);
        if (num >= 1 && num <= 12)
		{
            return (KeyboardKey)(KEY_F1 + (num - 1));
        }
    }

    // Common special keys (case-insensitive)
    if (strcasecmp(keystr, "SPACE") == 0)          return KEY_SPACE;
    if (strcasecmp(keystr, "ENTER") == 0 || 
        strcasecmp(keystr, "RETURN") == 0)         return KEY_ENTER;
    if (strcasecmp(keystr, "ESCAPE") == 0 || 
        strcasecmp(keystr, "ESC") == 0)            return KEY_ESCAPE;
    if (strcasecmp(keystr, "TAB") == 0)            return KEY_TAB;
    if (strcasecmp(keystr, "BACKSPACE") == 0)      return KEY_BACKSPACE;

    // Arrow keys
    if (strcasecmp(keystr, "LEFT") == 0)           return KEY_LEFT;
    if (strcasecmp(keystr, "RIGHT") == 0)          return KEY_RIGHT;
    if (strcasecmp(keystr, "UP") == 0)             return KEY_UP;
    if (strcasecmp(keystr, "DOWN") == 0)           return KEY_DOWN;

    // Modifiers
    if (strcasecmp(keystr, "LEFT_SHIFT") == 0)     return KEY_LEFT_SHIFT;
    if (strcasecmp(keystr, "RIGHT_SHIFT") == 0)    return KEY_RIGHT_SHIFT;
    if (strcasecmp(keystr, "LEFT_CONTROL") == 0)   return KEY_LEFT_CONTROL;
    if (strcasecmp(keystr, "RIGHT_CONTROL") == 0)  return KEY_RIGHT_CONTROL;
    if (strcasecmp(keystr, "LEFT_ALT") == 0)       return KEY_LEFT_ALT;
    if (strcasecmp(keystr, "RIGHT_ALT") == 0)      return KEY_RIGHT_ALT;

    //TraceLog(LOG_WARNING, "Unknown key value in bindings: '%s' - using KEY_NULL", keystr);
    
	return KEY_NULL;
}

// hardcoded defaults
static void rbg_set_default_bindings(void)
{
	/*
    inputBindings[INPUT_P1_MOVE_LEFT]  = KEY_A;
    inputBindings[INPUT_P1_MOVE_RIGHT] = KEY_D;
    inputBindings[INPUT_P1_MOVE_UP]    = KEY_W;
    inputBindings[INPUT_P1_MOVE_DOWN]  = KEY_S;
    inputBindings[INPUT_P1_JUMP]       = KEY_R;
    inputBindings[INPUT_P1_ATTACK]     = KEY_T;
    inputBindings[INPUT_F1]            = KEY_F1;
	*/
}

bool rbg_load_default_key_bindings(void)
{
	printf("\n=== loading default_key_bindings.json ===\n");

    // start from safe defaults
    rbg_set_default_bindings();

    // try to load JSON
    char* jsonText = LoadFileText("resources/default_key_bindings.json");
    if (jsonText == NULL)
    {
        TraceLog(LOG_WARNING, "Failed to load key bindings JSON - using hardcoded defaults");
        return false;
    }

    printf("\n%s", jsonText);

    cJSON* root = cJSON_Parse(jsonText);
    
	if (root == NULL || !cJSON_IsObject(root))
    {
        TraceLog(LOG_WARNING, "Failed to parse key bindings JSON: %s - using defaults", cJSON_GetErrorPtr());
        UnloadFileText(jsonText);
        return false;
    }

	for (int i = 0; i < INPUT_ACTION_COUNT; i++)
    {
        const char* actionName = rbg_input_action_names[i];
        cJSON* item = cJSON_GetObjectItem(root, actionName);

        if (item && cJSON_IsString(item))
        {
            const char* keyStr = cJSON_GetStringValue(item);
            KeyboardKey key = string_to_keyboard_key(keyStr);
            if (key != KEY_NULL)
            {
                inputBindings[i] = key;
                //TraceLog(LOG_INFO, "Loaded binding: %s -> %s", actionName, keyStr);
            }
            else
            {
                TraceLog(LOG_WARNING, "Invalid key value for %s: '%s' - keeping default", actionName, keyStr);
            }
        }
    }

    cJSON_Delete(root);
    UnloadFileText(jsonText);

    return true;
}

void rbg_init_input(void)
{
    rbg_load_default_key_bindings();
}

void rbg_update_input(void)
{
    // check down or pressed in every frame
    for (int i = 0; i < INPUT_ACTION_COUNT; i++)
    {
        downStates[i]    = IsKeyDown(inputBindings[i]);
        pressedStates[i] = IsKeyPressed(inputBindings[i]);
    }
}

InputAction rbg_get_move_left(int playerIndex)
{
	if (playerIndex == 1) return INPUT_P1_MOVE_LEFT;
	if (playerIndex == 2) return INPUT_P2_MOVE_LEFT;

	return 0;
}

InputAction rbg_get_move_right(int playerIndex)
{
	if (playerIndex == 1) return INPUT_P1_MOVE_RIGHT;
	if (playerIndex == 2) return INPUT_P2_MOVE_RIGHT;

	return 0;
}

InputAction rbg_get_move_up(int playerIndex)
{
	if (playerIndex == 1) return INPUT_P1_MOVE_UP;
	if (playerIndex == 2) return INPUT_P2_MOVE_UP;

	return 0;
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
   
    // simple released logic = was down last frame but not this frame
    return !downStates[action] && IsKeyUp(inputBindings[action]);
}
