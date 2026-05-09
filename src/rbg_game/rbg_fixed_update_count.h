#ifndef RBG_FIXED_UPDATE_COUNT_H
#define RBG_FIXED_UPDATE_COUNT_H

extern int rbg_fixed_updates;
extern double rbg_delta_time;
extern double rbg_accumulated_dt;

void rbg_init_fixed_update_count(void);
void rbg_fixed_update_count(void);

#endif
