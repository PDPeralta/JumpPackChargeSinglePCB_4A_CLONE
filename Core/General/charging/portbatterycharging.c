/*
 * portbatterycharging.c
 *
 *  Created on: Dec 15, 2021
 *      Author: peters
 */
#include "../General/charging/portbatterycharging.h"

#include "main.h"
#include <stdint.h>
#include "timer.h"

#include "../General/hw_interfaces/chargerBoard.h"
#include "../Platform_Specific/battMeasure.h"
#include "../Platform_Specific/chargePWM.h"

extern int IsPolarityReversed();

//Assign hardware specific control functions to charger porting layer

charger_t chargerPortFunctions = {.chargerMaxCurrent_mA = CHARGER_MAXCURRENT_MA,
                                  .PwmCC_MaxCurrent_DN = CC_MAXCURRENT_PWM_VAL,
                                  .ADCI_MaxCurrent_DN = 0,     //To be filled
                                  .ADCI_MinDetectionThreshold_DN = 0,  //To be filled
                                  .PwmCV_12V_DN = CV_12V_PWM_VAL,
                                  .ADCV_12V_DN = ADC_EXTBATT_12V_VALUE,
                                  .getPwm100PercentValue = PWM_Get100PercentValue,
                                  .ResetChargingTimeElapsed = resetSecondsElapsed,
                                  .GetChargingTimeElapsed_S = getSecondsElapsed,
                                  .Delay_ms = HAL_Delay,
                                  .ReadVoltage_DN = readExtBattVoltageDN,
                                  .ReadCurrent_DN = readExtBattCurrentDN,
                                  .ReadVoltage_mV = readExtBattmV,
                                  .ReadCurrent_mA = readExtBattCurrentmA,
                                  .IsReversePolarity = checkReversePolarity,
                                  .StartPWM_CC = PWM_CC_Start,
                                  .StopPWM_CC = PWM_CC_Stop,
                                  .SetPWM_CC = PWM_CC_SetDN,
                                  .SetPWM_mA = PWM_CC_SetmA,
                                  .StartPWM_CV = PWM_CV_Start,
                                  .StopPWM_CV = PWM_CV_Stop,
                                  .SetPWM_CV = PWM_CV_SetDN,
                                  };
