/*
 * batterycharging.c
 *
 *  Created on: Dec 13, 2021
 *      Author: peters
 */

#include "../General/charging/batterycharging.h"

#include <global_macros.h>
#include "main.h"
#include "../General/charge_parameters/chargeparams.h"
#include "../General/charging/portbatterycharging.h"

#define TASK_LOOP_SPEED_MS     200
#define BATT_WAIT_TIMEOUT_MS   2000
#define BATT_WAIT_NUM_LOOPS    BATT_WAIT_TIMEOUT_MS / TASK_LOOP_SPEED_MS

static batterychargestate_t BatteryChargeState = stateBatteryChargeWaitForBattery;
static batterychargeparameters_t *pBattChargeParams = NULL;
static charger_t *charger = NULL;

//Local functions
static batterychargestate_t BatteryChargeStopCharging(void);
static batterychargestate_t BatteryChargeWaitForBattery();
static batterychargestate_t BatteryChargeStart();
static batterychargestate_t BatteryChargeRecovery();
static batterychargestate_t BatteryChargeConstantCurrent();
static batterychargestate_t BatteryChargeConstantVoltage();
static batterychargestate_t BatteryChargeMaintenance();
static batterychargestate_t BatteryChargeError(batterychargestate_t BatteryChargeState);

static uint32_t pwmValue = 0;
static uint32_t outputCurrent_mA = 0;
static uint8_t waitForBattTimeout = 0;
static uint16_t battV_DN = 0;
static uint32_t batt_mV = 0;
static uint16_t battI_DN = 0;
static uint32_t batt_mA = 0;
//static uint16_t sulfationInitialmV = 0;
static uint32_t secondsTmp = 0;    //Holds time at transition to recovery, CC, CV

uint32_t getCCPwmFromCurrentmA(uint16_t currentDesired_mA)
{
    uint32_t dn = (currentDesired_mA * charger->PwmCC_MaxCurrent_DN) / charger->chargerMaxCurrent_mA;
    return dn;
}

uint32_t getCVPwmFromVoltagemV(uint16_t voltageDesired_mV)
{
    uint32_t dn = (voltageDesired_mV * charger->PwmCV_12V_DN) / 12000;
    return dn;
}

static batterychargestate_t TransitionChargeState(batterychargestate_t state)
{
    switch(state)
    {
    case stateBatteryChargeStopCharging:
        portIOcontrol.ExtBatt_ChgPathDisable();
        charger->StopPWM_CC();
        charger->StopPWM_CV();
        break;

    case stateBatteryChargeWaitForBattery:
    	portIOcontrol.ExtBatt_ChgPathDisable();
        charger->StopPWM_CC();
        charger->StopPWM_CV();
        break;

    case stateBatteryChargeStart:
        charger->StopPWM_CC();
        charger->StopPWM_CV();
        charger->ResetChargingTimeElapsed();
        break;

    case stateBatteryChargeRecovery:
        //Function BatteryChargeRecovery() sets the current output
        outputCurrent_mA = 0;
        charger->SetPWM_mA(1);
        //TODO: Get better name for batteryCCThreshold_mV - this the CV output value
        //TODO: Use mV units, not PWM DNs.
        pwmValue = getCVPwmFromVoltagemV(pBattChargeParams->batteryCCThreshold_mV);
        charger->SetPWM_CV(pwmValue);
        charger->StartPWM_CC();
        charger->StartPWM_CV();
        portIOcontrol.ExtBatt_ChgPathEnable();
        secondsTmp = charger->GetChargingTimeElapsed_S();
        break;

    case stateBatteryChargeConstantCurrent:
        //Leave current output alone - it was set in BatteryChargeRecovery();
        //Current output will ramp up in ChargeConstantCurrent() function
        //TODO: Get better name for batteryCCThreshold_mV - this the CV output value
        //TODO: Use mV units, not PWM DNs.
        pwmValue = getCVPwmFromVoltagemV(pBattChargeParams->batteryCCThreshold_mV);
        charger->SetPWM_CV(pwmValue);
        secondsTmp = charger->GetChargingTimeElapsed_S();
        break;

    case stateBatteryChargeConstantVoltage:
        //Leave current output alone - it was set in ChargeConstantCurrent();
        //TODO: Get better name for batteryCCThreshold_mV - this the CV output value
        //TODO: Use mV units, not PWM DNs.
        pwmValue = getCVPwmFromVoltagemV(pBattChargeParams->batteryCCThreshold_mV);
        charger->SetPWM_CV(pwmValue);
        secondsTmp = charger->GetChargingTimeElapsed_S();
        break;

    case stateBatteryChargeMaintenance:
        //Leave current output alone - it was set in ChargeConstantCurrent();
        //TODO: Use mV units, not PWM DNs.
        pwmValue = getCVPwmFromVoltagemV(pBattChargeParams->batteryMaintenanceOutput_mV);
        charger->SetPWM_CV(pwmValue);
        break;

    case stateBatteryChargeReversePolarity:
    	portIOcontrol.ExtBatt_ChgPathDisable();
        charger->StopPWM_CC();
        charger->StopPWM_CV();
        break;

    case stateBatteryChargeRecoveryTimeout:
    	portIOcontrol.ExtBatt_ChgPathDisable();
        charger->StopPWM_CC();
        charger->StopPWM_CV();
        break;

    case stateBatteryChargeSulfated:
    	portIOcontrol.ExtBatt_ChgPathDisable();
        charger->StopPWM_CC();
        charger->StopPWM_CV();
        break;

    case stateBatteryChargeCCTimeout:
    	portIOcontrol.ExtBatt_ChgPathDisable();
        charger->StopPWM_CC();
        charger->StopPWM_CV();
        break;

    case stateBatteryChargeExit:
    	portIOcontrol.ExtBatt_ChgPathDisable();
        charger->StopPWM_CC();
        charger->StopPWM_CV();
        break;
    }

    return state;
}

void AssertstateBatteryChargeStopCharging(void)
{
    TransitionChargeState(stateBatteryChargeStopCharging);
}

void DessertstateBatteryChargeStopCharging(void)
{
    TransitionChargeState(stateBatteryChargeWaitForBattery);
}

uint8_t IsBatteryDisconnected(void)
{
#if 0
    if(charger->ReadCurrent_DN() < charger->ADCI_MinDetectionThreshold_DN)
    {
        charger->StopPWM_CC();
        charger->StopPWM_CV();

        charger->Delay_ms(50);

        battV_DN = charger->ReadVoltage_DN();
        batt_mV = (12000 * battV_DN) / charger->ADCV_12V_DN;
        if(batt_mV < pBattChargeParams->batteryDetectionLevel_mV)
        {
            return 1;
        }
        else
        {
            charger->StartPWM_CC();
            charger->StartPWM_CV();
        }
    }

    return 0;
#endif
    uint32_t voltagemV = 0;
    uint32_t currentmA = 0;
    uint8_t belowstart = 0;

    //First check if there is current flow.
    //If there is current flow, return 0 - battery is connected.
    currentmA = charger->ReadCurrent_mA();
    //BatteryCurrentDetectionThreshold should be a parameter or determined at run time
    if (currentmA<100)
    {
        //If there is no current flow, disconnect FETs and read battery voltage
        //If we read less than start voltage three times in a row with 50 milli-sec delay, then there is no battery.
        //But first, let's make sure the current flow is below the threshold
        charger->Delay_ms(100);
        currentmA = charger->ReadCurrent_mA();
        //BatteryCurrentDetectionThreshold should be a parameter or determined at run time
        if (currentmA>100)
        {
            return 0;
        }

        //Now check reading battery voltage three times in a row
        portIOcontrol.ExtBatt_ChgPathDisable();
        charger->StopPWM_CC();
        charger->StopPWM_CV();
        charger->Delay_ms(100);
        voltagemV = charger->ReadVoltage_mV();
        if (voltagemV < StdAgmChargeParameters.batteryDetectionLevel_mV)
        {
            belowstart++;
        }
        charger->Delay_ms(50);
        voltagemV = charger->ReadVoltage_mV();
        if (voltagemV < StdAgmChargeParameters.batteryDetectionLevel_mV)
        {
            belowstart++;
        }
        charger->Delay_ms(50);
        voltagemV = charger->ReadVoltage_mV();
        if (voltagemV < StdAgmChargeParameters.batteryDetectionLevel_mV)
        {
            belowstart++;
        }

        if (belowstart == 3)
        {
            return 1;
        }
        else
        {
        	portIOcontrol.ExtBatt_ChgPathEnable();
            charger->StartPWM_CC();
            charger->StartPWM_CV();
            return 0;
        }
    }
    else
        return 0;
}

void resetBatteryChargeStateMachine(batterychargeparameters_t *battParamIn, charger_t *chargerPort)
{
    pBattChargeParams = battParamIn;
    charger = chargerPort;
    waitForBattTimeout = 0;
    BatteryChargeState = TransitionChargeState(stateBatteryChargeWaitForBattery);
}

batterychargestate_t batteryChargeStateMachine(void)
{
    charger->Delay_ms(TASK_LOOP_SPEED_MS);

    battV_DN = charger->ReadVoltage_DN();
    batt_mV = charger->ReadVoltage_mV(); //(12000 * battV_DN) / charger->ADCV_12V_DN;   //Convert DN read on ADC to millivolts based on known 12V DN value
    battI_DN = charger->ReadCurrent_DN();
    batt_mA = charger->ReadCurrent_mA(); //(charger->chargerMaxCurrent_mA * battI_DN) / charger->ADCI_MaxCurrent_DN;   //Convert DN read on ADC to mA based on known max current DN value

    switch (BatteryChargeState)
    {
    case stateBatteryChargeStopCharging:
        BatteryChargeState = BatteryChargeStopCharging();
        break;

    case stateBatteryChargeWaitForBattery:
        BatteryChargeState = BatteryChargeWaitForBattery();
        break;

    case stateBatteryChargeStart:
        BatteryChargeState = BatteryChargeStart();
        break;

    case stateBatteryChargeRecovery:
        BatteryChargeState = BatteryChargeRecovery();
        break;

    case stateBatteryChargeConstantCurrent:
        BatteryChargeState = BatteryChargeConstantCurrent();
        break;

    case stateBatteryChargeConstantVoltage:
        BatteryChargeState = BatteryChargeConstantVoltage();
        break;

    case stateBatteryChargeMaintenance:
        BatteryChargeState = BatteryChargeMaintenance();
        break;

    case stateBatteryChargeReversePolarity:
        BatteryChargeState = BatteryChargeError(BatteryChargeState);
        break;
    case stateBatteryChargeSulfated:
        BatteryChargeState = BatteryChargeError(BatteryChargeState);
        break;
    case stateBatteryChargeRecoveryTimeout:
        BatteryChargeState = BatteryChargeError(BatteryChargeState);
        break;
    case stateBatteryChargeCCTimeout:
        BatteryChargeState = BatteryChargeError(BatteryChargeState);
        break;
    case stateBatteryChargeExit:
        BatteryChargeState = BatteryChargeError(BatteryChargeState);
        break;
    }

    return BatteryChargeState;
}

batterychargestate_t BatteryChargeStopCharging(void)
{
    return stateBatteryChargeStopCharging;
}

batterychargestate_t BatteryChargeWaitForBattery()
{
    waitForBattTimeout++;
    if(waitForBattTimeout > BATT_WAIT_NUM_LOOPS)
    {
        return TransitionChargeState(stateBatteryChargeExit);
    }

    if(charger->IsReversePolarity())
    {
        return TransitionChargeState(stateBatteryChargeReversePolarity);
    }

    if(batt_mV > pBattChargeParams->batteryDetectionLevel_mV)
    {
        //SIMPLE_PRINT("Read ext. battery voltage %d mV - battery detected!\n", batt_mV);
        return TransitionChargeState(stateBatteryChargeStart);
    }
    else
    {
        //SIMPLE_PRINT("Read ext. battery voltage %d mV - too low, no battery detected...\n", batt_mV);
        return stateBatteryChargeWaitForBattery;
    }
}

batterychargestate_t BatteryChargeStart()
{
    if(charger->IsReversePolarity())
    {
        return TransitionChargeState(stateBatteryChargeReversePolarity);
    }

    if(batt_mV > pBattChargeParams->batteryDetectionLevel_mV)
    {
        if(charger->GetChargingTimeElapsed_S() > 8)
        {
            return TransitionChargeState(stateBatteryChargeRecovery);
        }
        else
        {
            return stateBatteryChargeStart;
        }
    }
    else
    {
        return TransitionChargeState(stateBatteryChargeWaitForBattery);
    }

    return stateBatteryChargeStart;
}

batterychargestate_t BatteryChargeRecovery()
{
    if(IsBatteryDisconnected())
    {
        return TransitionChargeState(stateBatteryChargeWaitForBattery);
    }

    //TODO: Do sulfation check if battery reads under 13V and is not lithium

    if(batt_mV <= pBattChargeParams->batteryRecoveryLevel1_mV)
    {
        //TODO: recovery current levels should be in parameters
        //TODO: Either put in current level of 100 mA for Lithium or just use 300 mA for all chemistries.
        charger->SetPWM_mA(200);
        outputCurrent_mA = 200;
        if((charger->GetChargingTimeElapsed_S() - secondsTmp) > pBattChargeParams->batteryRecoveryPeriod1_sec)
        {
            return TransitionChargeState(stateBatteryChargeRecoveryTimeout);
        }
    }
    else if(batt_mV < pBattChargeParams->batteryRecoveryLevel2_mV)
    {
        //TODO: recovery current levels should be in parameters
        charger->SetPWM_mA(300);
        outputCurrent_mA = 300;
        if((charger->GetChargingTimeElapsed_S() - secondsTmp) > pBattChargeParams->batteryRecoveryPeriod2_sec)
        {
            return TransitionChargeState(stateBatteryChargeRecoveryTimeout);
        }
    }
    else  //Voltage greater than recovery level 2, we are safe to start constant current charging
    {
        return TransitionChargeState(stateBatteryChargeConstantCurrent);
    }

    return stateBatteryChargeRecovery;
}

batterychargestate_t BatteryChargeConstantCurrent()
{
    if(IsBatteryDisconnected())
    {
        return TransitionChargeState(stateBatteryChargeWaitForBattery);
    }

    if((charger->GetChargingTimeElapsed_S() - secondsTmp) > pBattChargeParams->batteryCCMaxTime_sec)
    {
        return TransitionChargeState(stateBatteryChargeCCTimeout);
    }

    if(batt_mV < pBattChargeParams->batteryCCThreshold_mV)  //TODO: Change CCThreshold to be more clear it's Constant Voltage transition
    {
#if 0
        if(pwmValue < charger->PwmCC_MaxCurrent_DN)
        {
            pwmValue += 5;   //TODO: May want to compute increment based on current rate of charger
            charger->SetPWM_CC(pwmValue);
        }
        else if(pwmValue > charger->PwmCC_MaxCurrent_DN)
        {
            pwmValue = charger->PwmCC_MaxCurrent_DN;
            charger->SetPWM_CC(pwmValue);
        }
        else  //pwmValue == charger->PwmCC_MaxCurrent_DN
        {
            //Do nothing, PWMing at max current
        }
#else
        //TODO: put max current mA into parameter just like PwmCC_MaxCurrent_DN
        if (outputCurrent_mA < 4000)
        {
            outputCurrent_mA += 50;
            charger->SetPWM_mA(outputCurrent_mA);
        }
        else if (outputCurrent_mA > 4000)
        {
            outputCurrent_mA = 4000;
            charger->SetPWM_mA(outputCurrent_mA);
        }
        else  //outputCurrent_mA == 4000
        {
            //Do nothing, PWMing at max current
        }
#endif
    }
    else  //Voltage meets or exceeds CC threshold - we can now go to constant voltage
    {
        if((charger->GetChargingTimeElapsed_S() - secondsTmp) > 3600)
        {
            pBattChargeParams->batteryCVPeriod_sec = (2*(charger->GetChargingTimeElapsed_S() - secondsTmp)) / 3;   //If CC took over 1hr, make CV time 2/3 of CC time
            if(pBattChargeParams->batteryCVPeriod_sec > pBattChargeParams->batteryCVMaxTime_sec)
            {
                pBattChargeParams->batteryCVPeriod_sec = pBattChargeParams->batteryCVMaxTime_sec;  //Enforce maximum CV time
            }
        }
        else  if((charger->GetChargingTimeElapsed_S() - secondsTmp) > 240)  //Less than 1hr, more than 4 minutes
        {
            pBattChargeParams->batteryCVPeriod_sec = 1800;   //make CV time 30 minutes
        }
        else  //Less than 4 minutes CC time
        {
            pBattChargeParams->batteryCVPeriod_sec = 300;   //For testing purposes (#thanksJavi)
        }

        return TransitionChargeState(stateBatteryChargeConstantVoltage);
    }

    return stateBatteryChargeConstantCurrent;
}

batterychargestate_t BatteryChargeConstantVoltage()
{
    if(IsBatteryDisconnected())
    {
        return TransitionChargeState(stateBatteryChargeWaitForBattery);
    }

    if(batt_mV < pBattChargeParams->batteryReturnFromCV2CCThreshold_mV)
    {
    	//TODO: Save time spent in CV mode and restore it once returning to CV mode
        return TransitionChargeState(stateBatteryChargeConstantCurrent);
    }

    //if we are in CV mode for the max time, switch to Maintenance mode
    if ((charger->GetChargingTimeElapsed_S() - secondsTmp) >= pBattChargeParams->batteryCVMaxTime_sec)
	{
    	return TransitionChargeState(stateBatteryChargeMaintenance);
	}

    //if less than 200 mA of current and in CV for one minute, switch to Maintenance mode
	if ((batt_mA<=200) && ((charger->GetChargingTimeElapsed_S() - secondsTmp) >= 60))
	{
		return TransitionChargeState(stateBatteryChargeMaintenance);
	}

	//if less than 500 mA of current and in CV for greater than/equal to batteryCVPeriod_sec, switch to Maintenance mode
	if ((batt_mA<=500) && ((charger->GetChargingTimeElapsed_S() - secondsTmp) > pBattChargeParams->batteryCVPeriod_sec))
	{
		return TransitionChargeState(stateBatteryChargeMaintenance);
	}

	//if current > 500 mA reset time spent in CV mode
	if (batt_mA>500)
	{
		secondsTmp = charger->GetChargingTimeElapsed_S();
	}

    return stateBatteryChargeConstantVoltage;
}

batterychargestate_t BatteryChargeMaintenance()
{
    if(IsBatteryDisconnected())
    {
        return TransitionChargeState(stateBatteryChargeWaitForBattery);
    }

    if(batt_mV < pBattChargeParams->batteryCCRestartThreshold_mV)
    {
        return TransitionChargeState(stateBatteryChargeConstantCurrent);
    }

    return stateBatteryChargeMaintenance;
}

batterychargestate_t BatteryChargeError(batterychargestate_t BatteryChargeState)
{
    if((BatteryChargeState == stateBatteryChargeReversePolarity)  && !charger->IsReversePolarity())
    {
        return TransitionChargeState(stateBatteryChargeWaitForBattery);
    }

    return BatteryChargeState;
}
