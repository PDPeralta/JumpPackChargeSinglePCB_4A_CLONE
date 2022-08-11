/*
 * battMeasure.c
 *
 *  Created on: Dec 16, 2021
 *      Author: tjose
 */

#include "battMeasure.h"

#include <global_macros.h>

#include "../General/hw_interfaces/ioControl.h"
#include "../Platform_Specific/adcRead.h"

#define VREFINT_CAL *((uint16_t*) ((uint32_t) 0x1FFFF7BA))
uint16_t extBattCalFactorMv = 0;
uint16_t intBattCalFactorMv = 0;

uint16_t measureExtBattCalFactorAt12V(void)
{
    uint16_t measuredCalFactor = 0;

    //When we call this function, 12.0V should be applied to the battery clamps AND internal lithium pack terminals, for calibration

    setAdcChannel(EXT_BATT_V_ADC_CHANNEL);
    uint16_t adcRes = getAvgAdcResults(SAMPLE_AMT);
    //Calculate millivolts read on pin from adc result
    int16_t voltageMv = convertAdcValToMv((uint16_t)adcRes);
    uint16_t readVoltagemV = calcVoltageFromBatteryDivider(voltageMv, R1_Ext_BV, (R2_Ext_BV + DADBOD_DIDE_R_MODELED));  //Model the DADBOD diode as a 3K resistor

    if(readVoltagemV > 10000 && readVoltagemV < 14000)  //If we're not reading within these bounds, something is really wrong
    {
        if(readVoltagemV > 12000)
        {
            //We have a negative calibration factor we'll need to apply
            measuredCalFactor = readVoltagemV - 12000;
            measuredCalFactor |= 0x8000;   //Set MSB to indicate the factor is negative
        }
        else
        {
            //We have a positive cal factor
            measuredCalFactor = 12000 - readVoltagemV;
        }
        return measuredCalFactor;
    }
    else
    {
        return 0xFFFF;
    }
}

uint16_t measureIntBattCalFactorAt12V(void)
{
    uint16_t measuredCalFactor = 0;

    //When we call this function, 12.0V should be applied to the battery clamps AND internal lithium pack terminals, for calibration

    setAdcChannel(INT_BATT_V_ADC_CHANNEL);
    uint16_t adcRes = getAvgAdcResults(SAMPLE_AMT);
    //Calculate millivolts read on pin from adc result
    int16_t voltageMv = convertAdcValToMv((uint16_t)adcRes);
    uint16_t readVoltagemV = calcVoltageFromBatteryDivider(voltageMv, R1_Int_BV, R2_Int_BV);

    if(readVoltagemV > 10000 && readVoltagemV < 14000)  //If we're not reading within these bounds, something is really wrong
    {
        if(readVoltagemV > 12000)
        {
            //We have a negative calibration factor we'll need to apply
            measuredCalFactor = readVoltagemV - 12000;
            measuredCalFactor |= 0x8000;   //Set MSB to indicate the factor is negative
        }
        else
        {
            //We have a positive cal factor
            measuredCalFactor = 12000 - readVoltagemV;
        }
        return measuredCalFactor;
    }
    else
    {
        return 0xFFFF;
    }
}

void setCalFactors(uint16_t extFactor, uint16_t intFactor)
{
    extBattCalFactorMv = extFactor;
    intBattCalFactorMv = intFactor;
}

uint16_t readIntBattVoltageDN(void)
{
    setAdcChannel(INT_BATT_V_ADC_CHANNEL);
    return getAvgAdcResults(SAMPLE_AMT);
}

uint16_t readIntBattMv(void)
{
    uint16_t adcRes = readIntBattVoltageDN();

    //Calculate millivolts read on pin from adc result
    int16_t voltageMv = convertAdcValToMv((uint16_t)adcRes);
    voltageMv = calcVoltageFromBatteryDivider(voltageMv, R1_Int_BV, R2_Int_BV);

    if(intBattCalFactorMv & 0x8000)  //Apply negative cal factor if MSB set
    {
        if(voltageMv > (intBattCalFactorMv ^ 0x8000))
        {
            voltageMv -= (intBattCalFactorMv ^ 0x8000);
        }
    }
    else
    {
        voltageMv += intBattCalFactorMv;
    }

    return voltageMv;
}

uint16_t readExtBattVoltageDN(void)
{
    setAdcChannel(EXT_BATT_V_ADC_CHANNEL);
    return getAvgAdcResults(SAMPLE_AMT);
}

uint16_t readExtBattmV(void)
{
    uint16_t adcRes = readExtBattVoltageDN();

    //Calculate millivolts read on pin from adc result
    int16_t voltageMv = convertAdcValToMv((uint16_t)adcRes);
    voltageMv = calcVoltageFromBatteryDivider(voltageMv, R1_Ext_BV, (R2_Ext_BV + DADBOD_DIDE_R_MODELED));

    if(extBattCalFactorMv & 0x8000)  //Apply negative cal factor if MSB set
    {
        if(voltageMv > (extBattCalFactorMv ^ 0x8000))
        {
            voltageMv -= (extBattCalFactorMv ^ 0x8000);
        }
    }
    else
    {
        voltageMv += extBattCalFactorMv;
    }

    return voltageMv;
}

//ADC_V is tied into op-amp for battery charging
//In jump mode, op amp 5V bus is off
//Must turn on 5V bus to energize op amp
//Otherwise, op amp loads down ADC_V
//This function enables 5V, reads ADC_V, then disables 5V
uint16_t readExtBattmV_NonChargerMode(void)
{
    uint16_t mV = 0;
    portIOcontrol.USBAccChgPathEnable();
    HAL_Delay(100);
    mV = readExtBattmV();
    portIOcontrol.USBAccChgPathDisable();
    return mV;
}

uint16_t readExtBattCurrentDN(void)
{
    setAdcChannel(EXT_BATT_I_ADC_CHANNEL);
    return getAvgAdcResults(SAMPLE_AMT);
}

uint16_t readExtBattCurrentmA(void)
{
    uint16_t currentmA = 0;
    uint16_t adcRes = readExtBattCurrentDN();

    //Calculate millivolts read on pin from adc result
    int16_t voltageMv = convertAdcValToMv((uint16_t)adcRes);

    //Pull these from parameters, should not be hard coded
    //15 = milli-ohmm current sense resistor
    //40 = ADCI op amp gain
    //1000 = full scale of PWM I
    //3300 = full scale of I/O
    //To prevent integer round off, must scale voltageMv up by 1,000
    currentmA = (voltageMv*1000)/(15*45);

    return currentmA;
}

//TODO: This will either be dumped or replaced with opto-based method
//For now it will always return false/0
uint8_t checkReversePolarity(void)
{
#if 0
    if (readExtBattmV() >= V_RPP)  //If dadbod detects RPP, return 1 (true)
        return 1;
    else
        return 0;
#endif
    return 0;
}
