/*
 * battMeasure.h
 *
 *  Created on: Dec 16, 2021
 *      Author: tjose
 */

#ifndef PLATFORM_SPECIFIC_BATTMEASURE_H_
#define PLATFORM_SPECIFIC_BATTMEASURE_H_

#include "main.h"

#define INT_BATT_V_ADC_CHANNEL   ADC_CHANNEL_3     //Pin to internal lithium battery voltage divider
#define EXT_BATT_V_ADC_CHANNEL   ADC_CHANNEL_4     //Pin to DADBOD/external batt measure
#define EXT_BATT_I_ADC_CHANNEL   ADC_CHANNEL_5     //Current sense resistor ADC

//Internal Battery Voltage Divider Resistor Values
#define R1_Int_BV 39000
#define R2_Int_BV 10000

//External Battery Voltage Divider Resistor Values Plus Diode Drop
#define R1_Ext_BV 49900
#define R2_Ext_BV 10000
#define DADBOD_DIDE_R_MODELED   0

//Reverse Polarity Voltage, set to >15v
//DADBOD circuit puts ~3.3v (a little less through FET) on the ADC, corresponding to a pretend 18.975V that readExtBatt() would return,
//so we will consider a reading above 18V to be a reverse polarity condition
#define V_RPP 17500

uint16_t measureExtBattCalFactorAt12V(void);
uint16_t measureIntBattCalFactorAt12V(void);
void setCalFactors(uint16_t extFactor, uint16_t intFactor);
uint16_t readIntBattVoltageDN(void);
uint16_t readIntBattMv(void);
uint16_t readExtBattVoltageDN(void);
uint16_t readExtBattmV(void);
//ADC_V is tied into op-amp for battery charging
//In jump mode, op amp 5V bus is off
//Must turn on 5V bus to energize op amp
//Otherwise, op amp loads down ADC_V
//This function enables 5V, reads ADC_V, then disables 5V
uint16_t readExtBattmV_NonChargerMode(void);
uint16_t readExtBattCurrentDN(void);
uint16_t readExtBattCurrentmA(void);
uint8_t checkReversePolarity(void);

#endif /* PLATFORM_SPECIFIC_BATTMEASURE_H_ */
