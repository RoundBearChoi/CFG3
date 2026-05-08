#include "rbg_spritesheet_loader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

SpriteSheet *spritesheets = NULL;
int spritesheet_count = 0;

void LoadSpriteSheets(const char *csv_path)
{
    if (spritesheets != NULL)
	{
        UnloadSpriteSheets();   // allow re-load if called again
    }

    // First pass: count data rows (skip header)
    char *fileData = LoadFileText(csv_path);
    
	if (fileData == NULL) {
        TraceLog(LOG_WARNING, "Could not load spritesheet list: %s", csv_path);
        return;
    }

    int row_count = 0;
    char *line = strtok(fileData, "\r\n");
    
	if (line != NULL)
	{
        line = strtok(NULL, "\r\n");            // skip header
        while (line != NULL)
		{
            row_count++;
            line = strtok(NULL, "\r\n");
        }
    }

    UnloadFileText(fileData);

    if (row_count == 0) return;

    spritesheets = (SpriteSheet *)calloc(row_count, sizeof(SpriteSheet));
    
	if (spritesheets == NULL)
	{
        spritesheet_count = 0;
        TraceLog(LOG_ERROR, "Failed to allocate memory for spritesheets");
        return;
    }
    
	spritesheet_count = row_count;

    // Second pass: parse and load
    fileData = LoadFileText(csv_path);
    
	if (fileData == NULL)
	{
        free(spritesheets);
        spritesheets = NULL;
        spritesheet_count = 0;
        return;
    }

    line = strtok(fileData, "\r\n");    // header
	if (line) line = strtok(NULL, "\r\n");

	printf("\n=== loading textures ===\n");

	int i = 0;

	while (line != NULL && i < row_count)
	{
        char type_buf[64] = {0};
        char name_buf[128] = {0};   // may contain .png from CSV
        int tx = 0, ty = 0, ti = 0, pd = 0;
        float rs = 1.0f;

        int scanned = sscanf(line, "%63[^,],%127[^,],%d,%d,%d,%f,%d",
                             type_buf, name_buf, &tx, &ty, &ti, &rs, &pd);

        if (scanned >= 5)
		{
            // Strip .png extension if present (handles old and new CSV formats)
            char *ext = strrchr(name_buf, '.');
            if (ext && (strcmp(ext, ".png") == 0 || strcmp(ext, ".PNG") == 0))
			{
                *ext = '\0';   // truncate at the dot → clean base name
            }

            spritesheets[i].fighter_type = strdup(type_buf);
            spritesheets[i].spritesheet_name = strdup(name_buf);   // now guaranteed no .png
            spritesheets[i].total_x = tx;
            spritesheets[i].total_y = ty;
            spritesheets[i].total_images = ti;
            spritesheets[i].render_scale = rs;
            spritesheets[i].play_delay = pd;

            // Load texture using the clean name + .png
            char fullpath[512];
            snprintf(fullpath, sizeof(fullpath), "resource/fighters_spritesheets/%s.png", name_buf);
            spritesheets[i].texture = LoadTexture(fullpath);

            // Pre-compute frame size
            if (spritesheets[i].texture.id != 0 && tx > 0 && ty > 0)
			{
                spritesheets[i].frame_width = spritesheets[i].texture.width / tx;
                spritesheets[i].frame_height = spritesheets[i].texture.height / ty;
            } 
			else
			{
                spritesheets[i].frame_width = 0;
                spritesheets[i].frame_height = 0;
            }
        }

        i++;
        line = strtok(NULL, "\r\n");
    }

    UnloadFileText(fileData);
}

void UnloadSpriteSheets(void)
{
    if (spritesheets == NULL) return;

    for (int i = 0; i < spritesheet_count; i++)
	{
        if (spritesheets[i].texture.id != 0)
		{
            UnloadTexture(spritesheets[i].texture);
        }
        
		if (spritesheets[i].fighter_type) free(spritesheets[i].fighter_type);
        if (spritesheets[i].spritesheet_name) free(spritesheets[i].spritesheet_name);
    }

    free(spritesheets);
    spritesheets = NULL;
    spritesheet_count = 0;
}

SpriteSheet* GetSpriteSheetByName(const char *spritesheet_name)
{
    if (spritesheet_name == NULL || spritesheets == NULL) return NULL;

    for (int i = 0; i < spritesheet_count; i++)
	{
        if (spritesheets[i].spritesheet_name &&
            strcmp(spritesheets[i].spritesheet_name, spritesheet_name) == 0)
		{
            return &spritesheets[i];
        }
    }

    return NULL;
}
