#include "rbg_sheet_loader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void rbg_load_sprite_sheets(RbgGameContext* game_ctx, const char *csv_path)
{
    if (game_ctx->sprite_sheets != NULL)
	{
        rbg_unload_sprite_sheets(game_ctx);   // allow re-load if called again
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

    game_ctx->sprite_sheets = (sprite_sheet *)calloc(row_count, sizeof(sprite_sheet));
    
	if (game_ctx->sprite_sheets == NULL)
	{
        game_ctx->spritesheet_count = 0;
        TraceLog(LOG_ERROR, "Failed to allocate memory for sprite_sheets");
        return;
    }
    
	game_ctx->spritesheet_count = row_count;

    // Second pass: parse and load
    fileData = LoadFileText(csv_path);
    
	if (fileData == NULL)
	{
        free(game_ctx->sprite_sheets);
        game_ctx->sprite_sheets = NULL;
        game_ctx->spritesheet_count = 0;
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

            game_ctx->sprite_sheets[i].fighter_type = strdup(type_buf);
            game_ctx->sprite_sheets[i].spritesheet_name = strdup(name_buf);   // now guaranteed no .png
            game_ctx->sprite_sheets[i].total_x = tx;
            game_ctx->sprite_sheets[i].total_y = ty;
            game_ctx->sprite_sheets[i].total_images = ti;
            game_ctx->sprite_sheets[i].render_scale = rs;
            game_ctx->sprite_sheets[i].play_delay = pd;

            // Load texture using the clean name + .png
            char fullpath[512];
            snprintf(fullpath, sizeof(fullpath), "resources/fighters_spritesheets/%s.png", name_buf);
            game_ctx->sprite_sheets[i].texture = LoadTexture(fullpath);

            // Pre-compute frame size
            if (game_ctx->sprite_sheets[i].texture.id != 0 && tx > 0 && ty > 0)
			{
                game_ctx->sprite_sheets[i].frame_width = game_ctx->sprite_sheets[i].texture.width / tx;
                game_ctx->sprite_sheets[i].frame_height = game_ctx->sprite_sheets[i].texture.height / ty;
            } 
			else
			{
                game_ctx->sprite_sheets[i].frame_width = 0;
                game_ctx->sprite_sheets[i].frame_height = 0;
            }
        }

        i++;
        line = strtok(NULL, "\r\n");
    }

    UnloadFileText(fileData);
}

void rbg_unload_sprite_sheets(RbgGameContext* game_ctx)
{
	printf("\n=== unloading sprite sheets ===\n");

    if (game_ctx->sprite_sheets == NULL) return;

    for (int i = 0; i < game_ctx->spritesheet_count; i++)
	{
        if (game_ctx->sprite_sheets[i].texture.id != 0)
		{
            UnloadTexture(game_ctx->sprite_sheets[i].texture);
        }
        
		if (game_ctx->sprite_sheets[i].fighter_type) free(game_ctx->sprite_sheets[i].fighter_type);
        if (game_ctx->sprite_sheets[i].spritesheet_name) free(game_ctx->sprite_sheets[i].spritesheet_name);
    }

    free(game_ctx->sprite_sheets);
    game_ctx->sprite_sheets = NULL;
    game_ctx->spritesheet_count = 0;
}

sprite_sheet* rbg_get_sprite_sheet_by_name(RbgGameContext* game_ctx, const char *spritesheet_name)
{
    if (spritesheet_name == NULL || game_ctx->sprite_sheets == NULL) return NULL;

    for (int i = 0; i < game_ctx->spritesheet_count; i++)
	{
        if (game_ctx->sprite_sheets[i].spritesheet_name &&
            strcmp(game_ctx->sprite_sheets[i].spritesheet_name, spritesheet_name) == 0)
		{
            return &game_ctx->sprite_sheets[i];
        }
    }

    return NULL;
}
