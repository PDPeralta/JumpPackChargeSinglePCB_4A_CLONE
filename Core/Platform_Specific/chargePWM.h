/*
 * bulkPwm.h
 *
 *  Created on: Jan 4, 2022
 *      Author: tjose
 */

#ifndef PLATFORM_SPECIFIC_CHARGEPWM_H_
#define PLATFORM_SPECIFIC_CHARGEPWM_H_

#include "main.h"

void pwmConfigFrequency(uint16_t freq);
uint32_t PWM_Get100PercentValue();

void PWM_Bulk_Start();
void PWM_Bulk_Stop();
void PWM_Bulk_SetDutycycle(uint8_t dutycycle);

void PWM_CC_Start();
void PWM_CC_Stop();
void PWM_CC_SetDN(uint32_t DN);
void PWM_CC_SetmA(uint16_t mA);

void PWM_CV_Start();
void PWM_CV_Stop();
void PWM_CV_SetDN(uint32_t DN);

#endif /* PLATFORM_SPECIFIC_CHARGEPWM_H_ */
