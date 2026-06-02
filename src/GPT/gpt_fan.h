#ifndef  __GPT_FAN_H__
#define  __GPT_FAN_H__

#include "hal_data.h"


typedef enum e_wheel_direction
{
    e_wheel_stop                      = 0, ///<stop
    e_wheel_forward                   = 1, ///<forward
    e_wheel_reverse                   = 2  ///<reverse
} wheel_direction_t ;



void User_gpt_init(void);
void GPT_PWM_SetDuty(timer_ctrl_t *p_ctrl, uint8_t duty);
uint8_t Left_Wheel_control(wheel_direction_t wheel_Direction,uint32_t target_freq,uint32_t acquire_freq,uint8_t Duty);
uint8_t Right_Wheel_control(wheel_direction_t wheel_Direction,uint32_t target_freq,uint32_t acquire_freq,uint8_t Duty);


#endif /* __GPT_FAN_H__ */