#include "rbg_game_settings.h"
#include "../cJSON/cJSON.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

RBG_GameSettings global_rbg_game_settings = {false};

static char* read_file_to_string(const char* filename)
{
    FILE* file = fopen(filename, "rb");
    if (!file)
	{
        fprintf(stderr, "Failed to open %s\n", filename);
        return NULL;
    }
    
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    char* buffer = (char*)malloc(length + 1);
    if (!buffer)
	{
        fclose(file);
        return NULL;
    }
    
    size_t read = fread(buffer, 1, length, file);
    buffer[read] = '\0';
    fclose(file);
    
    return buffer;
}

void rbg_load_game_settings(const char* json_path)
{
	printf("\n=== loading game settings ===\n");

    const char* path = json_path ? json_path : "resources/game_settings.json";
    
    char* json_str = read_file_to_string(path);
    if (!json_str) 
	{
        fprintf(stderr, "Warning: Could not load game settings from %s (using defaults)\n", path);
        return;
    }
   
	printf("\n%s", json_str);

    cJSON* root = cJSON_Parse(json_str);
    free(json_str);
    
    if (!root)
	{
        fprintf(stderr, "Warning: Failed to parse game settings JSON: %s\n", cJSON_GetErrorPtr());
        return;
    }
    
    // Load render_debug (supports both bool and string literals)
    cJSON* item = cJSON_GetObjectItemCaseSensitive(root, "render_debug");
    
	if (cJSON_IsBool(item))
	{
        global_rbg_game_settings.render_debug = cJSON_IsTrue(item);
    }
	else if (cJSON_IsString(item))
	{
        // fallback for string literals
        const char* val = cJSON_GetStringValue(item);
        
		if (val)
		{
            if (strcasecmp(val, "true") == 0)
			{
                global_rbg_game_settings.render_debug = true;
            }
			else if (strcasecmp(val, "false") == 0)
			{
                global_rbg_game_settings.render_debug = false;
            }
        }
    }
    
    cJSON_Delete(root);
}
