/*
 * calibration.c
 *
 *  Created on: Jul 25, 2022
 *      Author: paulp
 */

#include "../General/charging/calibration.h"

#ifndef CHARGING_CALIBRATION_C_
#define CHARGING_CALIBRATION_C_

#if 0

uint16_t extCalFactor;
uint16_t intCalFactor;
void DoCalibration()
{
    //extCalFactor = measureExtBattCalFactorAt12V();
    //intCalFactor = measureIntBattCalFactorAt12V();

    if(extCalFactor == 0xFFFF || intCalFactor == 0xFFFF)   //Check if either measureCalFactor returned failed calibration values
    {
        extCalFactor = 0xFFFF;
        intCalFactor = 0xFFFF;
    }

    HAL_FLASH_Unlock();
    FLASH_EraseInitTypeDef eraseCfg = {.TypeErase = FLASH_TYPEERASE_PAGES, .PageAddress = 0x0800F800, .NbPages = 1};
    uint32_t pageError = 0;
    HAL_FLASHEx_Erase(&eraseCfg, &pageError);
    HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, 0x0800FFFC, extCalFactor);
    HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, 0x0800FFFE, intCalFactor);
    HAL_FLASH_Lock();

    if(extCalFactor != 0xFFFF && intCalFactor != 0xFFFF)
    {
        setLedsCalSuccess();   //If we did get valid cal values for both, blink both green LEDs for 4s to indicate success
        for(int i = 0; i < 4; i++)
        {
            delay_lowpower(1000);
        }
    }
}
void LoadCalibrationValues()
{
    extCalFactor = *(uint16_t*)(0x0800FFFC);
    intCalFactor = *(uint16_t*)(0x0800FFFE);
    if(extCalFactor != 0xFFFF && intCalFactor != 0xFFFF)
    {
        //setCalFactors(extCalFactor, intCalFactor);
    }
    else
    {
        setLedsErrUncalibrated();   //Blink charging red LED once every 5s
        while(1)
        {
            delay_lowpower(100);
        }
    }
}
#endif

#endif /* CHARGING_CALIBRATION_C_ */
