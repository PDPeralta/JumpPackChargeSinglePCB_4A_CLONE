/*
 * acDetect.c
 *
 *  Created on: Jan 21, 2022
 *      Author: tjose
 */

#include "../General/hw_interfaces/acDetect.h"

int acDetected(void)
{
    if(HAL_GPIO_ReadPin(AC_DET_GPIO_Port, AC_DET_Pin) == GPIO_PIN_RESET)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
