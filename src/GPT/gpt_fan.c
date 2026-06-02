#include "gpt_fan.h"

void gpt_fan_init(void)
{
    R_open(&g_timer_fan_ctrl, &g_timer_fan_cfg);
    R_timer_fan_ctrl_callback_set(&g_timer_fan_ctrl, gpt_fan_callback, NULL);
    R_timer_fan_ctrl_start(&g_timer_fan_ctrl);
}