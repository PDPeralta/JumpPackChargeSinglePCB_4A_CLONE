/*
 * state_transitions.c
 *
 *  Created on: Jul 27, 2022
 *      Author: paulp
 */
#include "state_transitions.h"
#include "timer.h"
#include "../General/hw_interfaces/ioControl.h"


void ErrorStateTransitionFxn()
{
    setLedsAllOff();

    portIOcontrol.ExtBatt_ChgPathDisable();
    portIOcontrol.IntBattAC_ChgPathDisable();
    portIOcontrol.IntBattUSB_ChgPathDisable();
    portIOcontrol.USBAccChgPathDisable();
    portIOcontrol.JumpRelay_Disable();
}

void IdleStateTransitionFxn()
{
    jumpAttempts = 0;
    chargerPortFunctions.StopPWM_CC();
    chargerPortFunctions.StopPWM_CV();
    portIOcontrol.ExtBatt_ChgPathDisable();
    portIOcontrol.IntBattAC_ChgPathDisable();
    portIOcontrol.IntBattUSB_ChgPathDisable();
    portIOcontrol.USBAccChgPathDisable();
    portIOcontrol.JumpRelay_Disable();
    setLedsAllOff();
}

void IdleLowBattStateTransitionFxn()
{
    chargerPortFunctions.StopPWM_CC();
    chargerPortFunctions.StopPWM_CV();
    portIOcontrol.ExtBatt_ChgPathDisable();
    portIOcontrol.IntBattAC_ChgPathDisable();
    portIOcontrol.IntBattUSB_ChgPathDisable();
    portIOcontrol.USBAccChgPathDisable();
    portIOcontrol.JumpRelay_Disable();
    setLedsAllOff();
}

void IntBattChargingStateTransitionFxn()
{
	portIOcontrol.IntBattUSB_ChgPathEnable();
    //setLedsChargingIntBatt();
}

void AcChargerIdleStateTransitionFxn()
{
    chargerPortFunctions.StopPWM_CC();
    chargerPortFunctions.StopPWM_CV();
    portIOcontrol.ExtBatt_ChgPathDisable();
    portIOcontrol.IntBattAC_ChgPathDisable();
    portIOcontrol.IntBattUSB_ChgPathDisable();
    //Run op amp from 5V DC
    portIOcontrol.USBAccChgPathEnable();
    portIOcontrol.JumpRelay_Disable();
    setLedsAllOff();
    setChgLedsWaitForBattery();

    if(selectedChemistry == StdAgmChemistry)
        setChemistryLeds(0, 1);
    else
        setChemistryLeds(1, 0);
}

void AcChargerChargingStateTransitionFxn()
{
    chargerPortFunctions.StopPWM_CC();
    chargerPortFunctions.StopPWM_CV();
    portIOcontrol.IntBattAC_ChgPathDisable();
    portIOcontrol.IntBattUSB_ChgPathDisable();
    //Run op amp from 5V DC
    portIOcontrol.USBAccChgPathEnable();
    portIOcontrol.JumpRelay_Disable();

    if(selectedChemistry == StdAgmChemistry)
        resetBatteryChargeStateMachine(&StdAgmChargeParameters, &chargerPortFunctions);
    else if(selectedChemistry == LithiumChemistry)
        resetBatteryChargeStateMachine(&LithiumChargeParameters, &chargerPortFunctions);

    resetSecondsElapsed();
}

void JumpWaitForBattStateTransitionFxn()
{
    setLedsAllOff();
    setJumpLedsWaitForBattery();
    chargerPortFunctions.StopPWM_CC();
    chargerPortFunctions.StopPWM_CV();
    portIOcontrol.ExtBatt_ChgPathDisable();
    portIOcontrol.IntBattUSB_ChgPathDisable();
    portIOcontrol.USBAccChgPathDisable();
}

void JumpJumpingStateTransitionFxn()
{
	portIOcontrol.JumpRelay_Enable();
    setJumpLedsJumping();
}

void JumpSuccessStateTransitionFxn()
{
	portIOcontrol.JumpRelay_Disable();
    //TODO: blink LEDs to indicated jumping succeeded!
}
