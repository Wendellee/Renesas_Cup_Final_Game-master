#ifndef  __GPT_FAN_H__
#define  __GPT_FAN_H__

#include "hal_data.h"
#include "common_utils.h"


/* Macros definitions */
#define GPT_MAX_PERCENT          (100U)             /* Max duty cycle percentage */

/* Function declarations */
fsp_err_t init_gpt_timer(timer_ctrl_t * const p_timer_ctl, timer_cfg_t const * const p_timer_cfg);
fsp_err_t start_gpt_timer(timer_ctrl_t * const p_timer_ctl);
fsp_err_t set_timer_duty_cycle(timer_ctrl_t * const p_ctrl, uint8_t duty_cycle_percent);
void deinit_gpt_timer(timer_ctrl_t * const p_timer_ctl);




#endif /* __GPT_FAN_H__ */
