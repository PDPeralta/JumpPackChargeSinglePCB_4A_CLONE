/*
 * portbatterycharging.h
 *
 *  Created on: Dec 15, 2021
 *      Author: peters
 */

#ifndef GENERAL_CHARGING_PORTBATTERYCHARGING_H_
#define GENERAL_CHARGING_PORTBATTERYCHARGING_H_

#include "main.h"


//See the README.md file for details

int AcPowerDetected(void);

uint16_t ReadExtBatteryVoltage_mV(void);
uint16_t ReadIntBatteryVoltage_mV(void);
uint16_t ReadOutputCurrent_DN(void);    //Only valid for models w/ current sense
int SetOutputVoltage_DN(uint16_t outputmV);
int SetOutputCurrent_DN(uint16_t ouptutmA);

void EnableExtBatOutput(void);
void EnableIntBatOutput(void);
void DisableExtBatOutput(void);
void DisableIntBatOutput(void);

int IsPolarityReversed();

uint32_t GetTime_seconds(void);
void Delay_ms(uint16_t delay_ms);

//PWM functions for "Junior-style" charging - no voltage or current control, just modulate bulk FET duty cycle based on voltage read feedback
void configBulkPwmFrequency(uint16_t freq);
void startBulkPWM();
void stopBulkPWM();
void setBulkPercentDutyCycle(uint8_t dutyCycle);

//PWM functions for higher current charging using op amp feedback and current sense circuitry
void configControlPwmFrequency(uint16_t freq);
void startPWM_CC();
void stopPWM_CC();
void setPWM_CC(uint16_t pwmVal);
void startPWM_CV();
void stopPWM_CV();
void setPWM_CV(uint16_t pwmVal);


typedef struct charger
{
    uint16_t chargerMaxCurrent_mA;
    uint32_t PwmCC_MaxCurrent_DN;     //PWM set value (in DNs) for charger's max current - probably from calibration
    uint16_t ADCI_MaxCurrent_DN;      //Current sense ADC read value (in DNs) for charger's max current reading - probably from calibration
    uint16_t ADCI_MinDetectionThreshold_DN;
    uint32_t PwmCV_12V_DN;            //PWM set value (in DNs) for 12V battery constant voltage - probably from calibration
    uint16_t ADCV_12V_DN;             //Voltage divider ADC read value (in DNs) for 12V battery reading - probably from calibration

    uint32_t (*getPwm100PercentValue)();
    void (*ResetChargingTimeElapsed)();
    uint32_t (*GetChargingTimeElapsed_S)();
    void (*Delay_ms)(uint32_t delay);
    uint16_t (*ReadVoltage_DN)();
    uint16_t (*ReadCurrent_DN)();
    uint16_t (*ReadVoltage_mV)();
    uint16_t (*ReadCurrent_mA)();
    uint8_t (*IsReversePolarity)();
    void (*StartPWM_CC)();
    void (*StopPWM_CC)();
    void (*SetPWM_CC)(uint32_t dn);
    void (*SetPWM_mA)(uint16_t mA);
    void (*StartPWM_CV)();
    void (*StopPWM_CV)();
    void (*SetPWM_CV)(uint32_t dn);

} charger_t;

extern charger_t chargerPortFunctions;

#endif /* GENERAL_CHARGING_PORTBATTERYCHARGING_H_ */
