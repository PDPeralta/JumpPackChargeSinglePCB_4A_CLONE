/*
 * states.c
 *
 *  Created on: Jul 26, 2022
 *      Author: paulp
 */

 //--FUCKITY: Abstract all the calls below

#include <global_macros.h>
#include "states.h"
#include "state_transitions.h"

#include "../General/hw_interfaces/ioControl.h"

uint16_t intBatt_mV;
uint16_t extBatt_mV;
uint32_t flags = 0;
uint8_t buttonHeld = 0;
uint8_t acJumpContention = 0;
uint8_t jumpAttempts = 0;
batterychargestate_t BatteryChargeState;
extern mainTaskState_t taskState;

void BatteryChargeStateMachine()
{
    BatteryChargeState = batteryChargeStateMachine();

    switch(BatteryChargeState)
    {
    case stateBatteryChargeStopCharging:
        break;
    case stateBatteryChargeWaitForBattery:
        setChgLedsWaitForBattery();
        break;
    case stateBatteryChargeStart:
        setChgLedsCharging();
        break;
    case stateBatteryChargeRecovery:
        break;
    case stateBatteryChargeConstantCurrent:
        setChgLedsCharging();
        break;
    case stateBatteryChargeConstantVoltage:
        setChgLedsConstantVoltage();
        break;
    case stateBatteryChargeMaintenance:
        setChgLedsMaintenance();
        break;
    case stateBatteryChargeReversePolarity:
        break;
    case stateBatteryChargeSulfated:
        break;
    case stateBatteryChargeRecoveryTimeout:
        break;
    case stateBatteryChargeCCTimeout:
        break;
    case stateBatteryChargeExit:
        break;
    }
}

//--DIGGITY: Format each case --> [Do a bunch of shit(put into a fxn)]and then change state (state stays at case level)
void TransitionState(mainTaskState_t state)
{
    switch(state)
    {
    case stRelayTestState:
        break;

    case stErrorState:

    	ErrorStateTransitionFxn();

        if(!flags)
        {
            taskState = stIdle;
        }
        else
        {
            if(flags & FLAG_REVPOLARITY)
            {
                setLedsErrorPolarity();
            }
            else if(flags & FLAG_SULFATED)
            {
                setChgLedsErrorSulfated();
            }
            else if(flags & FLAG_RECOVTIMEOUT)
            {
                setChgLedsErrorRecovTimeout();
            }
            else if(flags & FLAG_CCTIMEOUT)
            {
                setChgLedsErrorCCTimeout();
            }
            else if(flags & FLAG_JUMP_ERROR)
            {
                setJumpLedsFinshdJumping();
            }

            taskState = stErrorState;
        }
        break;

    case stIdle:
    	IdleStateTransitionFxn();
        taskState = stIdle;
        //goLowPowerState();
        break;

    case stIdleLowBatt:
    	IdleLowBattStateTransitionFxn();
        taskState = stIdleLowBatt;
        break;

    case stIntBattCharging:
    	IntBattChargingStateTransitionFxn();
        break;

    case stAcChargerIdle:
    	AcChargerIdleStateTransitionFxn();
        taskState = stAcChargerIdle;
        break;

    case stAcChargerCharging:
    	AcChargerChargingStateTransitionFxn();
        taskState = stAcChargerCharging;
        break;

    case stJumpWaitForBatt:
    	JumpWaitForBattStateTransitionFxn();
        taskState = stJumpWaitForBatt;
        break;

    case stJumpJumping:
    	JumpJumpingStateTransitionFxn();
        taskState = stJumpJumping;
        break;

    case stJumpSuccess:
    	JumpSuccessStateTransitionFxn();
        taskState = stJumpSuccess;
        break;
    }
}


void ErrorStateFxn()
{
    if(flags & (FLAG_REVPOLARITY | FLAG_SULFATED | FLAG_RECOVTIMEOUT | FLAG_CCTIMEOUT))
    {
        if(extBatt_mV < StdAgmChargeParameters.batteryDetectionLevel_mV)
        {
            flags &= ~(FLAG_REVPOLARITY | FLAG_SULFATED | FLAG_RECOVTIMEOUT | FLAG_CCTIMEOUT);
        }
    }
    else if(flags & FLAG_JUMP_ERROR)
    {
        if((isExtBatLoadOK() != OVERLOAD) && extBatt_mV < 1000)
        {
            flags &= ~FLAG_JUMP_ERROR;
        }
    }
    else
    {
        TransitionState(stIdle);
    }
}

void IdleStateFxn()
{
    //Should be in stop mode in this state (lowest power consumption possible)
    if(portIOcontrol.Detected_ACPower)
    {
        TransitionState(stAcChargerIdle);
    }
    else if(portIOcontrol.PluggedIn_JumpCable)
    {
        TransitionState(stJumpWaitForBatt);
    }
    else if(portIOcontrol.Detected_USBPowerInput && (intBatt_mV < (INTERNAL_BATT_MAINTAIN_LEVEL_MV - 150)))
    {
        TransitionState(stIntBattCharging);
    }
    else
    {
        //goLowPowerState();
    }
}

void IdleLowBattStateFxn()
{
    if(portIOcontrol.Detected_ACPower)
    {
        portIOcontrol.IntBattUSB_ChgPathDisable();
        portIOcontrol.IntBattAC_ChgPathEnable();
        //Display on int battery state of charge UI that we are charging
    }
    else
    {
        portIOcontrol.IntBattAC_ChgPathDisable();
        if(portIOcontrol.Detected_USBPowerInput)
        {
            portIOcontrol.IntBattUSB_ChgPathEnable();
            //Display on int battery state of charge UI that we are charging
        }
        else
        {
        	portIOcontrol.IntBattUSB_ChgPathDisable();
            //Turn off indication of charging on state of charge UI, or if full show full
        }
    }

    if(intBatt_mV > (INTERNAL_BATT_LOW_LEVEL_MV + 1000))
    {
        TransitionState(stIdle);
    }
    else
    {
		portIOcontrol.EnableLED_SOC1();
        delay_lowpower(500);
		portIOcontrol.DisableLED_SOC1();
        delay_lowpower(500);
    }
}

void IntBattChargingStateFxn()
{
    if(!portIOcontrol.Detected_USBPowerInput || intBatt_mV > (INTERNAL_BATT_MAINTAIN_LEVEL_MV + 150))
    {
        TransitionState(stIdle);
    }
    else if(portIOcontrol.Detected_ACPower)
    {
        TransitionState(stAcChargerIdle);
    }
    else if(portIOcontrol.PluggedIn_JumpCable)
    {
        TransitionState(stJumpWaitForBatt);
    }
}


void acChargerIdleStateFxn()
{
    if(portIOcontrol.Pressed_ChemSelButton)
    {
        if(!buttonHeld)
        {
            buttonHeld = 1;

            if(selectedChemistry == StdAgmChemistry)
            {
                selectedChemistry = LithiumChemistry;
                setChemistryLeds(1, 0);
            }
            else
            {
                selectedChemistry = StdAgmChemistry;
                setChemistryLeds(0, 1);
            }
        }
    }
    else
    {
        buttonHeld = 0;
    }

    if(extBatt_mV > StdAgmChargeParameters.batteryDetectionLevel_mV && !pcbaOvertemp)
    {
        TransitionState(stAcChargerCharging);
    }

    if(!portIOcontrol.Detected_ACPower)
    {
        TransitionState(stIdle);
    }
    else
    {
        if(intBatt_mV < INTERNAL_BATT_MAINTAIN_LEVEL_MV && !cellpackBadTemp)
        {
        	portIOcontrol.IntBattAC_ChgPathEnable();
            //Show in UI internal battery is charging
        }
        else if(intBatt_mV > (INTERNAL_BATT_MAINTAIN_LEVEL_MV + 150) || cellpackBadTemp)
        {
            portIOcontrol.IntBattAC_ChgPathDisable();
            //Turn off internal battery charging UI
        }

        if(portIOcontrol.PluggedIn_JumpCable)  //Jump cable is plugged in while connected to AC, indicate error
        {
            if(!acJumpContention)
            {
                acJumpContention = 1;
                setLedsAcJumpContention();
            }
        }
        else
        {
            if(acJumpContention)
            {
                acJumpContention = 0;
                TransitionState(stAcChargerIdle);   //This just sets the LEDs back to where they should be from jump contention state
            }

            //TODO: Don't think another button press block is necessary here
            if(portIOcontrol.Pressed_ChemSelButton)
            {
                if(!buttonHeld)
                {
                    buttonHeld = 1;

                    if(selectedChemistry == StdAgmChemistry)
                    {
                        selectedChemistry = LithiumChemistry;
                        setChemistryLeds(1, 0);
                    }
                    else
                    {
                        selectedChemistry = StdAgmChemistry;
                        setChemistryLeds(0, 1);
                    }
                }
            }
            else
            {
                buttonHeld = 0;
            }

            if(extBatt_mV > StdAgmChargeParameters.batteryDetectionLevel_mV && !pcbaOvertemp)
            {
                TransitionState(stAcChargerCharging);
            }
        }
    }
}

void acChargerChargingStateFxn()
{
    if(!portIOcontrol.Detected_ACPower)
    {
        TransitionState(stIdle);
        return;
    }
    else if(portIOcontrol.PluggedIn_JumpCable || pcbaOvertemp)
    {
        TransitionState(stAcChargerIdle);
        return;
    }
    //--FUCKITY: This should be in its own state machine function. Put it in the same folder as batteryChargeStateMachine()
    BatteryChargeStateMachine();

    if(BatteryChargeState == stateBatteryChargeExit)
    {
        TransitionState(stAcChargerIdle);
    }
    else if(BatteryChargeState > stateBatteryChargeMaintenance)
    {
        if(BatteryChargeState == stateBatteryChargeReversePolarity)
        {
            flags |= FLAG_REVPOLARITY;
        }
        else if(BatteryChargeState == stateBatteryChargeSulfated)
        {
            flags |= FLAG_SULFATED;
        }
        else if(BatteryChargeState == stateBatteryChargeRecoveryTimeout)
        {
            flags |= FLAG_RECOVTIMEOUT;
        }
        else if(BatteryChargeState == stateBatteryChargeCCTimeout)
        {
            flags |= FLAG_CCTIMEOUT;
        }

        TransitionState(stErrorState);
    }
}

void JumpWaitForBattStateFxn()
{
    if(!portIOcontrol.PluggedIn_JumpCable)
    {
        TransitionState(stIdle);
    }
    else if(portIOcontrol.Detected_ACPower)
    {
        TransitionState(stAcChargerIdle);
    }
    else  //Jump cable IS plugged in
    {
        if(intBatt_mV >= INTERNAL_BATT_JUMP_RDY_LEVEL_MV && !cellpackBadTemp)
        {
            setJumpLedsWaitForBattery();

            if(extBatt_mV > EXT_BATT_JUMP_DET_MV)   //Go ahead and jump if we simply read a voltage
            {
                TransitionState(stJumpJumping);
            }
#if 1  //TODO: Either dump or debug auto-force!
            else                                   //If can't read a significant voltage, try auto force for load detection
            {
                int loadStatus = isExtBatLoadOK();
                if(loadStatus == LOAD_OK)
                {
                    TransitionState(stJumpJumping);
                }
                else if(loadStatus == OVERLOAD)  //Clamps shorted or too high current load
                {
                    flags |= FLAG_JUMP_ERROR;
                    TransitionState(stErrorState);
                }
                else  //loadStatus == NO_LOAD_PRESENT, don't do anything
                {
                }
            }
#endif
        }
        else  //Internal battery is too low OR out of temperature range
        {
            setJumpLedsCellpackError();  //Indicate lithium pack problem
        }
    }
}

void JumpJumpingStateFxn()
{
    //Hold jump relay closed for 3.5s
    chargerPortFunctions.Delay_ms(3500);
    //Open jump relay
    portIOcontrol.JumpRelay_Disable();
    //Wait 1/2 second after opening relay
    chargerPortFunctions.Delay_ms(500);
    //TODO: Create state of jump success if extBatt_mV > 14900...
    //staying there waiting for battery disconnect/jump-cable removed
    extBatt_mV = readExtBattmV_NonChargerMode();
    if (extBatt_mV > 14900)
    {
        TransitionState(stJumpSuccess);
    }
    else
    {
        jumpAttempts++;
        if(jumpAttempts < MAX_JUMP_ATTEMPTS)
        {
            TransitionState(stJumpWaitForBatt);
        }
        else
        {
            flags |= FLAG_JUMP_ERROR;
            TransitionState(stErrorState);
        }
    }
}


void JumpSuccessStateFxn()
{
    if(!portIOcontrol.PluggedIn_JumpCable)
    {
        TransitionState(stIdle);
    }
    else if(portIOcontrol.Detected_ACPower)
    {
        TransitionState(stAcChargerIdle);
    }
    else if(extBatt_mV < EXT_BATT_JUMP_DET_MV)
    {
        TransitionState(stJumpWaitForBatt);
    }
}
