/*
 * led_control.h
 *
 *  Created on: Aug 1, 2022
 *      Author: paulp
 */

#ifndef GENERAL_LED_INDICATION_LED_CONTROL_H_
#define GENERAL_LED_INDICATION_LED_CONTROL_H_

#include "main.h"

#include "../General/hw_interfaces/ioControl.h"

typedef enum
{
	AutoForceState_0, //All Paths Open
	AutoForceState_1, //R_max, I_min
	AutoForceState_2,
	AutoForceState_3, //R_min, I_max
} AutoForceState_t;

#define AUTOFORCE_FETs_DISABLE  0
#define AUTOFORCE_50_OHM        1
#define AUTOFORCE_20_OHM        2
#define AUTOFORCE_14_OHM        3

void setLedChemistryAgm();
void setLedChemistryLith();
void setLedChgRed(uint8_t state);
void toggleLedChgRed();
void setLedChgGrn(uint8_t state);
void toggleLedChgGrn();
void setLedJumpRed(uint8_t state);
void toggleLedJumpRed();
void setLedJumpGrn(uint8_t state);
void toggleLedJumpGrn();
void setLedsStateOfCellpack(uint8_t numOn);   //Argument is number one out of 5

void setLedLight(uint8_t state);
void setTransformerEnable(uint8_t enable);
void setAutoforceFETs(AutoForceState_t level);  //LSB is AUTO_FORCE_3

#endif /* GENERAL_LED_INDICATION_LED_CONTROL_H_ */
