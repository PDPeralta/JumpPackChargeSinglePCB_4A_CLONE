/*
 * states.h
 *
 *  Created on: Jul 26, 2022
 *      Author: paulp
 */

#include "main.h"
#include "typedef.h"
#include "timer.h"

#include "../General/charge_parameters/chargeparams.h"
#include "../General/charging/batterycharging.h"
#include "../General/charging/portbatterycharging.h"
#include "../General/delay_lowpower/delay_lowpower.h"
#include "../General/jumping/batteryjumping.h"
#include "../General/led_indication/led_indication.h"
#include "../Platform_Specific/battMeasure.h"
#include "../Platform_Specific/tempMeasure.h"

#ifndef INC_STATES_H_
#define INC_STATES_H_

extern uint32_t flags;
extern uint16_t extBatt_mV;
extern uint16_t intBatt_mV;

void BatteryChargeStateMachine();
void TransitionState(mainTaskState_t state);

void ErrorStateFxn();
void IdleStateFxn();
void IdleLowBattStateFxn();
void IntBattChargingStateFxn();
void acChargerIdleStateFxn();
void acChargerChargingStateFxn();
void JumpWaitForBattStateFxn();
void JumpJumpingStateFxn();
void JumpSuccessStateFxn();

#endif /* INC_STATES_H_ */
