/*
 * adcRead.c
 *
 *  Created on: Dec 17, 2021
 *      Author: tjose
 */

#ifndef HW_INTERFACES_ADCREAD_C_
#define HW_INTERFACES_ADCREAD_C_

#include "adcRead.h"

#include <stdint.h>

extern ADC_HandleTypeDef hadc1;

void setAdcChannel(uint32_t channel)
{
//Configure ADC to the needed channel
    ADC_ChannelConfTypeDef channelConfig = { 0 };
    channelConfig.Channel = channel;
    channelConfig.Rank = ADC_REGULAR_RANK_1;
    channelConfig.SamplingTime = ADC_SAMPLETIME_79CYCLES_5;
    HAL_ADC_ConfigChannel(&hadc1, &channelConfig);
}

uint32_t readAdcValue()
{
    //HAL_ADCEx_Calibration_Start(&hadc1, ADC_SINGLE_ENDED);
//Perform conversion and read result
    if (HAL_ADC_Start(&hadc1) != HAL_OK)
    {
        return UINT32_MAX;
    }
    if (HAL_ADC_PollForConversion(&hadc1, 1000) != HAL_OK)
    {
        return UINT32_MAX;
    }
    uint32_t adcRes = HAL_ADC_GetValue(&hadc1);
    HAL_ADC_Stop(&hadc1);

    return adcRes;
}

uint32_t readArray[SAMPLE_AMT] = {0};
uint16_t getAvgAdcResults(uint8_t numSamples)
{
    uint32_t accumulator = 0;
    for (uint8_t i = 0; i < numSamples; i++)
    {
        readArray[i] = readAdcValue();
        accumulator += readArray[i];
    }

    uint16_t averagedAdcVal = accumulator / numSamples;
    return averagedAdcVal;
}

uint16_t calcVoltageFromBatteryDivider(uint16_t dividedVoltageMv, uint32_t R1, uint32_t R2)
{
    uint32_t n = (dividedVoltageMv) * (R2 + R1); //When called for dadbod voltage, diode drop is accounted for by resistor value R2
    uint32_t d = R2;

    return (uint16_t) (n / d);
}

uint16_t convertAdcValToMv(uint16_t adcVal)
{
    return (adcVal*ADC_VREF_MV) / ADC_FULLSCALE_BITS_12BIT;
}

#endif /* HW_INTERFACES_ADCREAD_C_ */
