/*
 * batteryjumping.h
 *
 *  Created on: Dec 16, 2021
 *      Author: paulp
 */

#ifndef GENERAL_JUMPING_BATTERYJUMPING_H_
#define GENERAL_JUMPING_BATTERYJUMPING_H_

#include <stdint.h>

typedef enum
{
    _14ohm,
    _20ohm,
    _50ohm,
} loadresistance_t;
//-----------------------------------------------------------------------------
// Macro Definitions
//-----------------------------------------------------------------------------
#define NOLOAD_THRESHOLD_MARGIN       2000   //Margin below internal batt. voltage which it must be within to assume no load
#define V_BAT_DETECT                  300    //Battery detection threshold

//For Stability check of ext battery voltage before jumping
#define ITERATION_AMT 5
#define ADC_STABILITYDELAY_MS 100
#define ALLOWABLE_MATCH_RANGE_MV 100
#define STABLE_AMT 1

//Return Values
#define NO_LOAD_PRESENT 0
#define LOAD_OK 1
#define OVERLOAD -1

//-----------------------------------------------------------------------------
// Function Prototypes
//-----------------------------------------------------------------------------
int8_t isExtBatLoadOK(void);
void setCurrentLtdPath(uint8_t resistance);
uint16_t isExtVoltageStable(void);
void openCurrentLtdPaths();

#endif /* GENERAL_JUMPING_BATTERYJUMPING_H_ */
