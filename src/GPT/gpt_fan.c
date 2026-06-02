#include "gpt_fan.h"
//GPT定时器控制风扇转动
void gpt_fan_init(void)
{
    //
    R_GPT_Open(&g_timer6_ctrl,&g_timer6_cfg);
    R_GPT_OutputDisable(&g_timer6_ctrl,GPT_IO_PIN_GTIOCA);
    R_GPT_OutputDisable(&g_timer6_ctrl,GPT_IO_PIN_GTIOCB);
    R_GPT_Start(&g_timer6_ctrl);
    //Left_Wheel_control(e_wheel_forward,1000,0,80);
    R_GPT_Open(&g_timer7_ctrl,&g_timer7_cfg);
    R_GPT_OutputDisable(&g_timer7_ctrl,GPT_IO_PIN_GTIOCA);
    R_GPT_OutputDisable(&g_timer7_ctrl,GPT_IO_PIN_GTIOCB);
    R_GPT_Start(&g_timer7_ctrl);
    //Right_Wheel_control(e_wheel_forward,1000,0,80);
    R_GPT_Open(&g_timer8_ctrl,&g_timer8_cfg);
    R_GPT_OutputDisable(&g_timer8_ctrl,GPT_IO_PIN_GTIOCA);
    R_GPT_OutputDisable(&g_timer8_ctrl,GPT_IO_PIN_GTIOCB);
    R_GPT_Start(&g_timer8_ctrl);
}


//设置GPT占空比
void GPT_PWM_SetDuty(timer_ctrl_t *p_ctrl, uint8_t duty)
{
    timer_info_t info;
    uint32_t current_period_counts;
    uint32_t duty_cycle_counts;

    if (duty > 100)
        duty = 100; //限制占空比范围：0~100

    /* 获得GPT的信息 */
    R_GPT_InfoGet(p_ctrl, &info);

    /* 获得计时器一个周期需要的计数次数 */
    current_period_counts = info.period_counts;

    /* 根据占空比和一个周期的计数次数计算GTCCR寄存器的值 */
    duty_cycle_counts = (uint32_t)(((uint64_t) current_period_counts * duty) / 100);

    /* 最后调用FSP库函数设置占空比 */
    R_GPT_DutyCycleSet(p_ctrl, duty_cycle_counts, GPT_IO_PIN_GTIOCA);
    R_GPT_DutyCycleSet(p_ctrl, duty_cycle_counts, GPT_IO_PIN_GTIOCB);
}

//控制左右轮转动
uint8_t Left_Wheel_control(wheel_direction_t wheel_Direction,uint32_t target_freq,uint32_t acquire_freq,uint8_t Duty)
{
    if( e_wheel_forward == wheel_Direction )
    {
        R_GPT_OutputEnable(&g_timer7_ctrl,GPT_IO_PIN_GTIOCA);
        R_GPT_OutputDisable(&g_timer7_ctrl,GPT_IO_PIN_GTIOCB);
    }
    else if( e_wheel_reverse == wheel_Direction)
    {
        R_GPT_OutputEnable(&g_timer7_ctrl,GPT_IO_PIN_GTIOCB);
        R_GPT_OutputDisable(&g_timer7_ctrl,GPT_IO_PIN_GTIOCA);
    }
    else if( e_wheel_stop == wheel_Direction)
    {
        R_GPT_OutputDisable(&g_timer7_ctrl,GPT_IO_PIN_GTIOCA);
        R_GPT_OutputDisable(&g_timer7_ctrl,GPT_IO_PIN_GTIOCB);
    }
   // R_BSP_SoftwareDelay(500,BSP_DELAY_UNITS_MILLISECONDS);
    if(acquire_freq >= target_freq - 200 && acquire_freq <= target_freq + 200)
        {
            GPT_PWM_SetDuty(&g_timer7_ctrl,Duty);
        }
        else if(acquire_freq <= target_freq - 200)
        {
            Duty+=1;
            GPT_PWM_SetDuty(&g_timer7_ctrl,Duty);
        }
        else if(acquire_freq >= target_freq + 200)
        {
            Duty-=1;
            GPT_PWM_SetDuty(&g_timer7_ctrl,Duty);
        }
        //R_BSP_SoftwareDelay(500,BSP_DELAY_UNITS_MILLISECONDS);

        return Duty;
}
//控制左右轮转动
uint8_t Right_Wheel_control(wheel_direction_t wheel_Direction,uint32_t target_freq,uint32_t acquire_freq,uint8_t Duty)
{
    if( e_wheel_forward == wheel_Direction )
    {
        R_GPT_OutputEnable(&g_timer8_ctrl,GPT_IO_PIN_GTIOCA);
        R_GPT_OutputDisable(&g_timer8_ctrl,GPT_IO_PIN_GTIOCB);
    }
    else if( e_wheel_reverse == wheel_Direction)
    {
        R_GPT_OutputEnable(&g_timer8_ctrl,GPT_IO_PIN_GTIOCB);
        R_GPT_OutputDisable(&g_timer8_ctrl,GPT_IO_PIN_GTIOCA);
    }
    else if( e_wheel_stop == wheel_Direction)
    {
        R_GPT_OutputDisable(&g_timer8_ctrl,GPT_IO_PIN_GTIOCA);
        R_GPT_OutputDisable(&g_timer8_ctrl,GPT_IO_PIN_GTIOCB);
    }
   // R_BSP_SoftwareDelay(500,BSP_DELAY_UNITS_MILLISECONDS);
    if(acquire_freq >= target_freq - 200 && acquire_freq <= target_freq + 200)
        {
            GPT_PWM_SetDuty(&g_timer8_ctrl,Duty);
        }
        else if(acquire_freq <= target_freq - 200)
        {
            Duty+=1;
            GPT_PWM_SetDuty(&g_timer8_ctrl,Duty);
        }
        else if(acquire_freq >= target_freq + 200)
        {
            Duty-=1;
            GPT_PWM_SetDuty(&g_timer8_ctrl,Duty);
        }
        //R_BSP_SoftwareDelay(500,BSP_DELAY_UNITS_MILLISECONDS);

        return Duty;
}
