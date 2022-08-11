/*
 * delay_lowpower.c
 *
 *  Created on: Apr 7, 2022
 *      Author: tjose
 */

#include "../General/delay_lowpower/delay_lowpower.h"

#include "stm32c0xx_hal.h"

extern RTC_HandleTypeDef hrtc;

void delay_lowpower(int delayMs)
{
#if 0
FOOME
    uint32_t wakeupCnt = delayMs * 10;
    HAL_RTCEx_SetWakeUpTimer_IT(&hrtc, wakeupCnt, RTC_WAKEUPCLOCK_RTCCLK_DIV4);
    HAL_SuspendTick();

    HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);

    HAL_RTCEx_DeactivateWakeUpTimer(&hrtc);
    HAL_ResumeTick();
#endif
}

//TODO: Have to de-init ADC and re-init ADC when we come out of this sleep mode
void goLowPowerState()
{
#if 0
FOOME
    HAL_SuspendTick();

    HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);

    HAL_ResumeTick();
#endif
}
