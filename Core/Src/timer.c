/*
 * timer.c
 *
 *  Created on: Jul 25, 2022
 *      Author: paulp
 */

#include "timer.h"
#include "typedef.h"
#include "main.h"

extern mainTaskState_t taskState;

uint8_t timCnt = 0;  //TODO: Make this more clear
uint32_t secondsCnt = 0;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    //FOOME if(htim->Instance == TIM6)  //TIM6 is used for LED blinking
    {
        //Call LED tick function
        tickLedMachine();

        //Increment tim_cnt for seconds counting if charging
        if(taskState == stAcChargerCharging)
        {
            timCnt++;
            if(timCnt > 1)
            {
                secondsCnt++;
            }
        }
    }
}

void resetSecondsElapsed()
{
    timCnt = 0;
    secondsCnt = 0;
}
uint32_t getSecondsElapsed()
{
    return secondsCnt;
}
