#ifndef RBG_GAME_H
#define RBG_GAME_H

#include <stdbool.h>

extern double global_rbg_frame_time;

typedef struct {
    bool game_initialized;
    // Add more game-wide state here later
} RbgGameContext;

void rbg_init_game(void);
void rbg_run_game(RbgGameContext* game_ctx);

#endif
