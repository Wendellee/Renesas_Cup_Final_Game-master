/***********************************************************************************************************************
 * File Name    : gpt_timer.c
 * Description  : Contains function definition.
 **********************************************************************************************************************/
/***********************************************************************************************************************
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/

#include "gpt_fan.h"

/*******************************************************************************************************************//**
 * @addtogroup r_gpt_ep
 * @{
 **********************************************************************************************************************/
/* Store Timer open state */
//uint8_t g_timer_open_state = RESET_VALUE;//Store Timer open state, default value is 0, which means the timer is not open,when the timer is open in periodic mode

/***********************************************************************************************************************
 * @brief       Initialize GPT timer
 * @param[in]   p_timer_ctl     Timer instance control structure
 * @param[in]   p_timer_cfg     Timer instance Configuration structure
 * @param[in]   timer_mode      Mode of GPT Timer
 * @retval      FSP_SUCCESS     Upon successful open of timer
 * @retval      Any Other Error code apart from FSP_SUCCESS on Unsuccessful open
 **********************************************************************************************************************/
fsp_err_t init_gpt_timer(timer_ctrl_t * const p_timer_ctl, timer_cfg_t const * const p_timer_cfg)
{
    fsp_err_t err = FSP_SUCCESS;

    /* Initialize GPT Timer */
    err = R_GPT_Open(p_timer_ctl, p_timer_cfg);
    if (FSP_SUCCESS != err)
    {
        APP_ERR_PRINT ("\r\n** R_GPT_Open API FAILED **\r\n");
        return err;
    }
    APP_PRINT("GPT timer initialized successfully.\r\n");
    return err;
    
}

/***********************************************************************************************************************
 * @brief       Start GPT timers in Periodic, One-Shot, PWM mode
 * @param[in]   p_timer_ctl     Timer instance control structure
 * @retval      FSP_SUCCESS     Upon successful start of timer
 * @retval      Any Other Error code apart from FSP_SUCCESS on Unsuccessful start
 **********************************************************************************************************************/
fsp_err_t start_gpt_timer (timer_ctrl_t * const p_timer_ctl)
{
    fsp_err_t err = FSP_SUCCESS;

    /* Starts GPT timer */
    err = R_GPT_Start(p_timer_ctl);
    if (FSP_SUCCESS != err)
    {
        /* In case of GPT_open is successful and start fails, requires a immediate cleanup.
         * Since, cleanup for GPT open is done in start_gpt_timer, hence cleanup is not required */
        APP_ERR_PRINT ("\r\n** R_GPT_Start API failed **\r\n");
    }
    APP_PRINT("GPT timer started successfully.\r\n");
    return err;
    
}

/***********************************************************************************************************************
 *  @brief       Set duty cycle of PWM timer
 *  @param[in]   duty_cycle_percent
 *  @retval      FSP_SUCCESS on correct duty cycle set
 *  @retval      FSP_INVALID_ARGUMENT on invalid info
 **********************************************************************************************************************/
fsp_err_t set_timer_duty_cycle(timer_ctrl_t * const p_ctrl, uint8_t duty_cycle_percent)
{
    fsp_err_t err                           = FSP_SUCCESS;
    uint32_t duty_cycle_counts              = RESET_VALUE;
    uint32_t current_period_counts          = RESET_VALUE;
    timer_info_t info                       = {(timer_direction_t)RESET_VALUE, RESET_VALUE, RESET_VALUE};

    /* Get the current period setting */
    err = R_GPT_InfoGet(p_ctrl, &info);
    if (FSP_SUCCESS != err)
    {
        /* GPT Timer InfoGet Failure message */
        APP_ERR_PRINT ("\r\n** R_GPT_InfoGet API failed **\r\n");
    }
    else
    {
        /* Update period counts locally */
        current_period_counts = info.period_counts;

        /* Calculate the desired duty cycle based on the current period. Note that if the period could be larger than
         * UINT32_MAX / 100, this calculation could overflow. A cast to uint64_t is used to prevent this. The cast is
         * not required for 16-bit timers. */
        duty_cycle_counts = (uint32_t) ((uint64_t) (current_period_counts * duty_cycle_percent) / GPT_MAX_PERCENT);

        err = R_GPT_DutyCycleSet(p_ctrl, duty_cycle_counts, GPT_IO_PIN_GTIOCB);
        if (FSP_SUCCESS != err)
        {
            /* GPT Timer duty cycle set failure message */
            /* In case of GPT_open is successful and duty cycle set fails, requires a immediate cleanup.
             * Since, cleanup for GPT open is done in timer_duty_cycle_set, hence cleanup is not required */
            APP_ERR_PRINT ("\r\n** R_GPT_DutyCycleSet API failed **\r\n");
        }
    }
    APP_PRINT("GPT timer duty cycle set successfully.\r\n");
    return err;
    
}

///***********************************************************************************************************************
// * @brief      Close the GPT HAL driver
// * @param[in]  p_timer_ctl     Timer instance control structure
// * @retval     None
// **********************************************************************************************************************/
//void deinit_gpt_timer(timer_ctrl_t * const p_timer_ctl)
//{
//    fsp_err_t err = FSP_SUCCESS;
//
//    /* Timer Close API call */
//    err = R_GPT_Close(p_timer_ctl);
//    if (FSP_SUCCESS != err)
//    {
//        /* GPT Close failure message */
//        APP_ERR_PRINT ("\r\n** R_GPT_Close FAILED **\r\n");
//    }
//
//    /* Reset open state of timer */
//    g_timer_open_state = RESET_VALUE;
//}


