#include "rbg_single_sprite_loader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void rbg_load_single_sprites(RbgGameContext* game_ctx, const char *csv_path)
{
    if (game_ctx->single_sprites != NULL)
    {
        rbg_unload_single_sprites(game_ctx);   // allow re-load if called again
    }

    // First pass: count data rows (skip header)
    char *fileData = LoadFileText(csv_path);
    
    if (fileData == NULL) {
        TraceLog(LOG_WARNING, "Could not load single sprite list: %s", csv_path);
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

    game_ctx->single_sprites = (single_sprite *)calloc(row_count, sizeof(single_sprite));
    
    if (game_ctx->single_sprites == NULL)
    {
        game_ctx->single_sprite_count = 0;
        TraceLog(LOG_ERROR, "Failed to allocate memory for single_sprites");
        return;
    }
    
    game_ctx->single_sprite_count = row_count;

    // Second pass: parse and load
    fileData = LoadFileText(csv_path);
    
    if (fileData == NULL)
    {
        free(game_ctx->single_sprites);
        game_ctx->single_sprites = NULL;
        game_ctx->single_sprite_count = 0;
        return;
    }

    line = strtok(fileData, "\r\n");    // header
    if (line) line = strtok(NULL, "\r\n");

    printf("\n=== loading single sprites ===\n");

    int i = 0;

    while (line != NULL && i < row_count)
    {
        char name_buf[128] = {0};

        // Single column CSV – take the whole line
        if (sscanf(line, "%127[^\r\n]", name_buf) >= 1)
        {
            // Strip .png extension if present (same logic as sheet loader)
            char *ext = strrchr(name_buf, '.');
            if (ext && (strcmp(ext, ".png") == 0 || strcmp(ext, ".PNG") == 0))
            {
                *ext = '\0';   // truncate at the dot → clean base name
            }

            game_ctx->single_sprites[i].sprite_name = strdup(name_buf);

            // Load texture
            char fullpath[512];
            snprintf(fullpath, sizeof(fullpath), "resources/single_sprites/%s.png", name_buf);
            game_ctx->single_sprites[i].texture = LoadTexture(fullpath);

            // Optional but recommended for pixel art text
            if (game_ctx->single_sprites[i].texture.id != 0)
            {
                SetTextureFilter(game_ctx->single_sprites[i].texture, TEXTURE_FILTER_POINT);
            }
        }

        i++;
        line = strtok(NULL, "\r\n");
    }

    UnloadFileText(fileData);
}

void rbg_unload_single_sprites(RbgGameContext* game_ctx)
{
    printf("\n=== unloading single sprites ===\n");

    if (game_ctx->single_sprites == NULL) return;

    for (int i = 0; i < game_ctx->single_sprite_count; i++)
    {
        if (game_ctx->single_sprites[i].texture.id != 0)
        {
            UnloadTexture(game_ctx->single_sprites[i].texture);
        }
        
        if (game_ctx->single_sprites[i].sprite_name)
        {
            free(game_ctx->single_sprites[i].sprite_name);
        }
    }

    free(game_ctx->single_sprites);
    game_ctx->single_sprites = NULL;
    game_ctx->single_sprite_count = 0;
}

single_sprite* rbg_get_single_sprite_by_name(RbgGameContext* game_ctx, const char *sprite_name)
{
    if (sprite_name == NULL || game_ctx->single_sprites == NULL) return NULL;

    for (int i = 0; i < game_ctx->single_sprite_count; i++)
    {
        if (game_ctx->single_sprites[i].sprite_name &&
            strcmp(game_ctx->single_sprites[i].sprite_name, sprite_name) == 0)
        {
            return &game_ctx->single_sprites[i];
        }
    }

    return NULL;
}
