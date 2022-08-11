/*
 * batteryjumping.c
 *
 *  Created on: Dec 16, 2021
 *      Author: paulp
 */
#include "../General/jumping/batteryjumping.h"

#include "main.h"

#include "../General/charging/portbatterycharging.h"
#include "../General/led_indication/led_control.h"
#include "../Platform_Specific/battMeasure.h"

int8_t isExtBatLoadOK(void)    //Signed return value for each state.
{
    //loadresistance_t resistance = _125ohm;
    uint16_t currentLtdVoltage = 0;
    uint16_t intBattMv = readIntBattMv();
    setAutoforceFETs(AutoForceState_1);
    HAL_Delay(50);
    currentLtdVoltage = readExtBattmV_NonChargerMode(); //Store current limited state voltage
    openCurrentLtdPaths();

    HAL_Delay(200);

    if(currentLtdVoltage >= (intBattMv - NOLOAD_THRESHOLD_MARGIN))
    {
        return NO_LOAD_PRESENT;
    }
    else if(currentLtdVoltage > 2000 /*should be comparing to min detectable battery voltage for charging V_BAT_DETECT*/)
    {
        return LOAD_OK;
    }
    else
    {
        return OVERLOAD;
    }

    /*
    for (resistance = _125ohm; resistance > _15ohm; resistance--) //Iterate through decreasing resistance (increasing current) paths
    {
        setCurrentLtdPath(resistance);             //Enable current limited path
        Delay_ms(50);
        currentLtdVoltage = readExtBattmV_NonChargerMode(); //Store current limited state voltage
        openCurrentLtdPaths(); //Disable all current limited paths for safety and to prevent false dadbod readings

        Delay_ms(200); //Total pulse period 50ms, 10ms ON and 40ms OFF.

        if ((resistance == _125ohm) && (currentLtdVoltage >= (intBattMv - NOLOAD_THRESHOLD_MARGIN))) //If initial current path is within 0.5v of the internal battery
        {
            return NO_LOAD_PRESENT;
        }

        if (currentLtdVoltage > V_BAT_DETECT) //If current limited path puts dadbod above noise floor
        {
            return LOAD_OK;   //Will eventually allow for JUMP
        }

    } //End FOR

    return OVERLOAD;  //ERROR, LOAD MUST BE TOO HIGH
    */
}

void setCurrentLtdPath(loadresistance_t resistance)
{
    switch (resistance)
    {
    case _50ohm:   //R_eq = 125 Ohms
        setAutoforceFETs(AUTOFORCE_50_OHM);
        break;

    case _20ohm:   //R_eq = 50 Ohms
        setAutoforceFETs(AUTOFORCE_20_OHM);
        break;

    case _14ohm:   //R_eq = 36 Ohms
        setAutoforceFETs(AUTOFORCE_14_OHM);
        break;

    default:
        break;

    } // End Switch

}

//Function for determining if ADC actually reads a voltage meeting jump requirements
//or if clamps were simply removed, ensuring unit won't
//go into JUMP MODE whilst clamps are being removed
uint16_t isExtVoltageStable(void)
{
    uint16_t baseline = 0;
    uint8_t counter = 0;
    int n;
    baseline = readExtBattmV_NonChargerMode();     //Store dadbod voltage reading as a baseline

    for (n = 0; n < ITERATION_AMT; n++) //Checking for stabilized clamp voltage for defined amt. of iterations
    {
        Delay_ms(ADC_STABILITYDELAY_MS); //Delay to allow for full clamp removal
        uint16_t dadbod_mV = readExtBattmV_NonChargerMode();      //Read new dadbod after delay

        if ((dadbod_mV >= (baseline - ALLOWABLE_MATCH_RANGE_MV)) && (dadbod_mV <= (baseline + ALLOWABLE_MATCH_RANGE_MV))) //If voltage has not changed (within a defined
        {                             // threshold) before & after delay
            counter++; //Increment counter for total amount of same ADC readings
        }
        else
        {
            baseline = dadbod_mV; //Else, set a new baseline and re-check for same voltages
            counter = 0;            //Reset counter if adc value changes,
        }
        if (counter == STABLE_AMT) //If we have X (TBD) consecutive readings between delays, assume they actually want to jump
        {
            return 1;
        }
    }  //End FOR loop

    return 0; //Error triggered if ADC cannot determine a stable value within defined (ITERATION_AMT) number of attempts
}  //End function

void openCurrentLtdPaths()
{
    setAutoforceFETs(AUTOFORCE_FETs_DISABLE);
}
