/*
 * state_transitions.h
 *
 *  Created on: Jul 27, 2022
 *      Author: paulp
 */

#include <global_macros.h>

#include "../General/charge_parameters/chargeparams.h"
#include "../General/led_indication/led_indication.h"

#ifndef INC_STATE_TRANSITIONS_H_
#define INC_STATE_TRANSITIONS_H_


extern uint8_t jumpAttempts;

void ErrorStateTransitionFxn();
void IdleStateTransitionFxn();
void IdleLowBattStateTransitionFxn();
void IntBattChargingStateTransitionFxn();
void AcChargerIdleStateTransitionFxn();
void AcChargerChargingStateTransitionFxn();
void JumpWaitForBattStateTransitionFxn();
void JumpJumpingStateTransitionFxn();
void JumpSuccessStateTransitionFxn();

#endif /* INC_STATE_TRANSITIONS_H_ */
