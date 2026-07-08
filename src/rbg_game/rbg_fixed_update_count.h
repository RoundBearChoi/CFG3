#ifndef RBG_FIXED_UPDATE_COUNT_H
#define RBG_FIXED_UPDATE_COUNT_H

extern int global_rbg_fixed_updates;
extern double global_rbg_accumulated_dt;

void rbg_init_fixed_update_count(void);
void rbg_fixed_update_count(void);

#endif
