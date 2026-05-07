#include "rbg_update_input.h"
#include "../../cJSON/cJSON.h"
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

// static -> internal linkage -> function is visible only inside the current translation unit -> not declared in header
// Helper: Convert JSON value (e.g. "a", "D", "space" later) to KeyboardKey
static KeyboardKey string_to_keyboard_key(const char* keystr)
{
    if (keystr == NULL || keystr[0] == '\0') {
        return KEY_NULL;
    }

    char c = keystr[0];

    // Lowercase or uppercase letter → KEY_A .. KEY_Z
    if ((c >= 'a' && c <= 'z')) {
        return (KeyboardKey)(KEY_A + (c - 'a'));
    }
    if ((c >= 'A' && c <= 'Z')) {
        return (KeyboardKey)(KEY_A + (c - 'A'));
    }

    return KEY_NULL;  // fallback
}

void rbg_init_init(void)
{
	rbg_load_default_key_bindings();
}

void rbg_load_default_key_bindings(void)
{
	// Try to load from JSON
    char* jsonText = LoadFileText("resource/default_key_bindings.json");
    
	if (jsonText == NULL)
	{
        TraceLog(LOG_WARNING, "Failed to load key bindings JSON - using defaults");
        return;
    }

	printf("\nprinting default_key_bindings.json...\n");
	printf(jsonText);

    cJSON* root = cJSON_Parse(jsonText);
    if (root == NULL || !cJSON_IsObject(root))
	{
        TraceLog(LOG_WARNING, "Failed to parse key bindings JSON: %s", cJSON_GetErrorPtr());
        UnloadFileText(jsonText);
        return;
    }

	// Override defaults with values from JSON
    bool anyLoaded = false;
    for (int i = 0; i < INPUT_ACTION_COUNT; i++)
	{
        const char* actionName = rbg_input_action_names[i];
        cJSON* item = cJSON_GetObjectItem(root, actionName);

        if (item && cJSON_IsString(item)) {
            const char* keyStr = cJSON_GetStringValue(item);
            KeyboardKey key = string_to_keyboard_key(keyStr);
            if (key != KEY_NULL) {
                inputBindings[i] = key;
                anyLoaded = true;
            } else {
                TraceLog(LOG_WARNING, "Invalid key value for %s: '%s' - keeping default", actionName, keyStr);
            }
        }
    }

    if (anyLoaded)
	{
        TraceLog(LOG_INFO, "Key bindings loaded successfully from JSON");
    }

    cJSON_Delete(root);
    UnloadFileText(jsonText);
}

void rbg_update_input(void)
{
	// run once
	if (input_initialized == false)
	{
		input_initialized = true;
		rbg_init_init();
	}

	// check down or pressed in every frame
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
