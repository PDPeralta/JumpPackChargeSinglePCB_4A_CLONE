/*
 * extInterrupts.c
 *
 *  Created on: Jul 26, 2022
 *      Author: paulp
 */

#include "../General/hw_interfaces/extInterrupts.h"


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    switch(GPIO_Pin)
    {
    case AC_DET_Pin:      //Plugged into AC power
        break;
    case JUMP_DET_Pin:    //Jump cable plugged in
        break;
    case USB_DET_Pin:     //USB power plugged in
        break;
    case BTN_WAKE_Pin:    //Display internal cellpack SOC
        break;
    case BTN_LIGHT_Pin:   //Toggle LED light
        break;

    default:
        break;
    }
}
