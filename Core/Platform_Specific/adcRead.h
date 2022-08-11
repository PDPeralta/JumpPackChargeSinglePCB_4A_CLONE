/*
 * adcRead.h
 *
 *  Created on: Dec 17, 2021
 *      Author: tjose
 */

#ifndef PLATFORM_SPECIFIC_ADCREAD_H_
#define PLATFORM_SPECIFIC_ADCREAD_H_

#include "main.h"

#define ADC_FULLSCALE_BITS_12BIT     ((1 << 12)-1) // 12 bit ADC
#define ADC_FULLSCALE_BITS_10BIT     ((1 << 10)-1) // 10 bit ADC
#define ADC_VREF_MV                  (3300UL)    //In STM32F301xx devices, VREF+ and VDDA are internally connected (see ST RM0366)

#define SAMPLE_AMT 10    //Number of samples to average in getAvgAdcResults()

void setAdcChannel(uint32_t channel);
uint32_t readAdcValue();
uint16_t getAvgAdcResults(uint8_t numSamples);
uint16_t convertAdcValToMv(uint16_t adcVal);
uint16_t calcVoltageFromBatteryDivider(uint16_t dividedVoltageMv, uint32_t R1, uint32_t R2);

#endif /* PLATFORM_SPECIFIC_ADCREAD_H_ */
