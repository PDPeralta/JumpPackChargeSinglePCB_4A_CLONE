/*
 * test.c
 *
 *  Created on: Jul 26, 2022
 *      Author: paulp
 */

#include "../General/testing/test.h"
/*

    //PWM test code
    uint16_t mAout=0;
    uint32_t pwmVal = 0;
    uint32_t voltagemV = 0;
    uint32_t currentmA = 0;
    ENABLE_USB_ACCESSORY_CHG;  //Powering Op-Amp through the 5V output

    CLOSE_JUMP_RELAY;
    HAL_Delay(1000);
    extBatt_mV = readExtBattmV();
    OPEN_JUMP_RELAY;
    HAL_Delay(1000);
    extBatt_mV = readExtBattmV();

    DISABLE_USB_ACCESSORY_CHG;
    CLOSE_JUMP_RELAY;
    HAL_Delay(1000);
    extBatt_mV = readExtBattmV();
    OPEN_JUMP_RELAY;
    HAL_Delay(1000);
    extBatt_mV = readExtBattmV();

    PWM_CV_Start();
    PWM_CV_SetDN(1000);   //1000 is full scale maximum ~16.25 V, 750 ~14.0 V
    PWM_CC_Start();
    PWM_CC_SetDN(100);
    ENABLE_EXTBATT_CHG_PATH;
    //FOOME do not use port expander setTransformerEnable(1);

    while(1)
    {

        if(pwmVal < 1000)
        {
            pwmVal+= 100;
            PWM_CC_SetDN(pwmVal);
        }
#else
        if (mAout < 5000)
        {
            PWM_CC_SetmA(mAout);
            mAout += 500;
        }

        HAL_Delay(100);

        voltagemV = readExtBattmV();
        currentmA = readExtBattCurrentmA();

    }

*/




#if 0    //Test Code for Current Ltd. 1A Output
    uint32_t intbatvoltagemV = 0;
    uint32_t extbatvoltagemV = 0;
    uint32_t result = 0;

    ENABLE_USB_ACCESSORY_CHG;  //Powering Op-Amp through the 5V output
    intbatvoltagemV = readIntBattMv();
    extbatvoltagemV = readExtBattmV();

    //Enable 1A Current Ltd. Output
    setI2cGpioShadow(AUTOFORCE_1_EXPANDER_POS_bm);
    pushI2cGpioShadow();
    setI2cGpioShadow(AUTOFORCE_2_EXPANDER_POS_bm);
    pushI2cGpioShadow();
    setI2cGpioShadow(AUTOFORCE_3_EXPANDER_POS_bm);
    pushI2cGpioShadow();

    //HAL_Delay(200);
    intbatvoltagemV = readIntBattMv();
    extbatvoltagemV = readExtBattmV();
    result = intbatvoltagemV - extbatvoltagemV;

    DISABLE_USB_ACCESSORY_CHG;  //Powering Op-Amp through the 5V output
    clearI2cGpioShadow(AUTOFORCE_1_EXPANDER_POS_bm);
    pushI2cGpioShadow();
    clearI2cGpioShadow(AUTOFORCE_2_EXPANDER_POS_bm);
    pushI2cGpioShadow();
    clearI2cGpioShadow(AUTOFORCE_3_EXPANDER_POS_bm);
    pushI2cGpioShadow();

    HAL_Delay(200);

#endif
