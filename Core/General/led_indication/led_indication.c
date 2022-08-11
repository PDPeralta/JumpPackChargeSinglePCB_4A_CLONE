/*
 * led_indication.c
 *
 *  Created on: Apr 8, 2022
 *      Author: tjose
 */

#include "../General/led_indication/led_indication.h"

#include <global_macros.h>

#include "../General/led_indication/led_control.h"

static const uint8_t blinkPattern1blink[10] = {1,0,0,0,0,0,0,0,0,0};
static const uint8_t blinkPattern2blink[10] = {1,0,1,0,0,0,0,0,0,0};
static const uint8_t blinkPattern3blink[10] = {1,0,1,0,1,0,0,0,0,0};
static uint8_t blinkIndex = 0;

enum generalUiErrorState
{
    generalUiNoErrorDisp,
    generalUiUncalibrated,
    generalUiCalSuccess,
    generalUiTestBlink,
    generalUiErrorPolarity,
    generalUiErrorAcJumpContention,
    generalUiErrorLowCellpack,
} generalUiErrorState = generalUiNoErrorDisp;  //If in any state besides generalUiNoErrorDisp, UI error indication will override LED functionality

enum chgUiState
{
    chgUiOff,
    chgUiWaitingForBattery,
    chgUiCharging,
    chgUiConstantVoltage,
    chgUiMaintenance,
    chgUiErrSulfated,
    chgUiErrRecovTimeout,
    chgUiErrCCTimeout,
} chgUiState = chgUiOff;    //State of red/green charging LED pair. Chemistry LEDs aren't as dynamic so they're controlled separately

enum jmpUiState
{
    jmpUiOff,
    jmpUiWaitingForBattery,
    jmpUiJumping,
    jmpUiFinishedJumping,
    jmpUiCellpackError,
} jmpUiState = jmpUiOff;

enum cellpackUiState
{
    cellpackUiStateOff,
    cellpackUiStateShow,
} cellpackUiState = cellpackUiStateOff;
uint8_t cellpackChgLevel = 0;   //Out of 5 to display on 5 LEDs

void setCellpackChgLevelIndication(int cpack_mV)
{
    if(cpack_mV > INTERNAL_BATT_MAINTAIN_LEVEL_MV)
    {
        cellpackChgLevel = 5;
    }
    else if(cpack_mV > 14500)
    {
        cellpackChgLevel = 4;
    }
    else if(cpack_mV > INTERNAL_BATT_JUMP_RDY_LEVEL_MV)
    {
        cellpackChgLevel = 3;
    }
    else if(cpack_mV > INTERNAL_BATT_ACC_CHARGE_LEVEL_MV)
    {
        cellpackChgLevel = 2;
    }
    else if(cpack_mV > INTERNAL_BATT_LOW_LEVEL_MV)
    {
        cellpackChgLevel = 1;
    }
    else
    {
        cellpackChgLevel = 0;
    }

    setLedsStateOfCellpack(cellpackChgLevel);
}

void tickLedMachine()
{
    if(generalUiErrorState == generalUiNoErrorDisp)
    {
        switch(chgUiState)
        {
            case chgUiOff:
                break;
            case chgUiWaitingForBattery:
                toggleLedChgRed();
                break;
            case chgUiCharging:
                //Red chg LED is solid on, no blinking
                break;
            case chgUiConstantVoltage:
                toggleLedChgGrn();
                break;
            case chgUiMaintenance:
                //Green chg LED is solid on, no blinking
                break;
            case chgUiErrSulfated:
                //Red and green 1 blink per 5s
                if(blinkPattern1blink[blinkIndex])
                {
                	portIOcontrol.EnableLED_ChgAmb();
                	portIOcontrol.EnableLED_ChgGrn();
                }
                else
                {
                	portIOcontrol.DisableLED_ChgAmb();
                	portIOcontrol.DisableLED_ChgGrn();
                }

                if(blinkIndex < (sizeof(blinkPattern1blink)-1))
                    blinkIndex++;
                else
                    blinkIndex = 0;
                break;
            case chgUiErrRecovTimeout:
                //Red and green 2 blink per 5s
                if(blinkPattern2blink[blinkIndex])
                {
                	portIOcontrol.EnableLED_ChgAmb();
                	portIOcontrol.EnableLED_ChgGrn();
                }
                else
                {
                	portIOcontrol.DisableLED_ChgAmb();
                	portIOcontrol.DisableLED_ChgGrn();
                }

                if(blinkIndex < (sizeof(blinkPattern2blink)-1))
                    blinkIndex++;
                else
                    blinkIndex = 0;
                break;
            case chgUiErrCCTimeout:
                //Red and green 3 blink per 5s
                if(blinkPattern3blink[blinkIndex])
                {
                	portIOcontrol.EnableLED_ChgAmb();
                	portIOcontrol.EnableLED_ChgGrn();
                }
                else
                {
                	portIOcontrol.DisableLED_ChgAmb();
                	portIOcontrol.DisableLED_ChgGrn();
                }

                if(blinkIndex < (sizeof(blinkPattern3blink)-1))
                    blinkIndex++;
                else
                    blinkIndex = 0;
                break;

            default:
                break;
        }

        switch(jmpUiState)
        {
        case jmpUiOff:
            break;
        case jmpUiWaitingForBattery:
            toggleLedJumpGrn();
            break;
        case jmpUiJumping:
            //Green jump LED solid on, no blinking
            break;
        case jmpUiFinishedJumping:
            //Red jump LED solid red, no blinking
            break;
        case jmpUiCellpackError:
            toggleLedJumpRed();
            break;

        default:
            break;
        }
    }
    else
    {
        switch(generalUiErrorState)
        {
        case generalUiNoErrorDisp:
            break;
        case generalUiUncalibrated:
            if(blinkPattern1blink[blinkIndex])
            {
            	portIOcontrol.EnableLED_ChgAmb();
            	portIOcontrol.EnableLED_ChgGrn();
            }
            else
            {
            	portIOcontrol.DisableLED_ChgAmb();
            	portIOcontrol.DisableLED_ChgGrn();
            }

            if(blinkIndex < (sizeof(blinkPattern1blink)-1))
                blinkIndex++;
            else
                blinkIndex = 0;
            break;
        case generalUiCalSuccess:
        	portIOcontrol.ToggleLED_ChgGrn();
        	portIOcontrol.ToggleLED_JmpGrn();
            break;
        case generalUiTestBlink:
        	portIOcontrol.ToggleLED_ALL();
            break;
        case generalUiErrorPolarity:
        	portIOcontrol.ToggleLED_ChgAmb();
        	portIOcontrol.ToggleLED_ChgGrn();
            break;
        case generalUiErrorAcJumpContention:
        	portIOcontrol.ToggleLED_ChgAmb();
        	portIOcontrol.ToggleLED_JmpAmb();
            break;
        case generalUiErrorLowCellpack:
            if(blinkPattern1blink[blinkIndex])
            {
            	portIOcontrol.EnableLED_JmpAmb();
            }
            else
            {
            	portIOcontrol.DisableLED_JmpAmb();
            }

            if(blinkIndex < (sizeof(blinkPattern1blink)-1))
                blinkIndex++;
            else
                blinkIndex = 0;

            break;

        default:
            break;
        }
    }
}

void setLedsAllOn()
{
    generalUiErrorState = generalUiNoErrorDisp;
    chgUiState = chgUiOff;
    jmpUiState = jmpUiOff;
    portIOcontrol.EnableLED_ALL();
}
void setLedsAllOff()
{
    generalUiErrorState = generalUiNoErrorDisp;
    chgUiState = chgUiOff;
    jmpUiState = jmpUiOff;
    portIOcontrol.DisableLED_ALL();
}

void setChgLedsOff()
{
    chgUiState = chgUiOff;
    portIOcontrol.DisableLED_ChgAmb();
    portIOcontrol.DisableLED_ChgGrn();
    portIOcontrol.DisableLED_Agm();
    portIOcontrol.DisableLED_Lithium();
}
void setJumpLedsOff()
{
    jmpUiState = jmpUiOff;
    portIOcontrol.DisableLED_JmpAmb();
    portIOcontrol.DisableLED_JmpGrn();
}


void setLedsErrUncalibrated()   //Flash red slow sequence
{
    if(generalUiErrorState != generalUiUncalibrated)
    {
        setLedsAllOff();
        generalUiErrorState = generalUiUncalibrated;
    }
}

void setLedsCalSuccess()   //Flash both greens
{
    if(generalUiErrorState != generalUiCalSuccess)
    {
        setLedsAllOff();
        generalUiErrorState = generalUiCalSuccess;
    }
}

void doLedTestSequence()
{
    if(generalUiErrorState != generalUiTestBlink)
    {
        setLedsAllOff();
        generalUiErrorState = generalUiTestBlink;
    }
}

void setChemistryLeds(int lithiumLed, int agmLed)
{
    if(lithiumLed)
    	portIOcontrol.EnableLED_Lithium();
    else
    	portIOcontrol.DisableLED_Lithium();
    if(agmLed)
    	portIOcontrol.EnableLED_Agm();
    else
    	portIOcontrol.DisableLED_Agm();

}

void setChgLedsWaitForBattery()  //Flashing red
{
    if(chgUiState != chgUiWaitingForBattery)
    {
    	portIOcontrol.DisableLED_ChgAmb();
    	portIOcontrol.DisableLED_ChgGrn();
        chgUiState = chgUiWaitingForBattery;
    }
}
void setChgLedsCharging()   //Solid red
{
    if(chgUiState != chgUiCharging)
    {
    	portIOcontrol.EnableLED_ChgAmb();
    	portIOcontrol.DisableLED_ChgGrn();
        chgUiState = chgUiCharging;
    }
}
void setChgLedsConstantVoltage()   //Solid red + Flashing green
{
    if(chgUiState != chgUiConstantVoltage)
    {
    	portIOcontrol.EnableLED_ChgAmb();
    	portIOcontrol.DisableLED_ChgGrn();
        chgUiState = chgUiConstantVoltage;
    }
}
void setChgLedsMaintenance()    //Solid green
{
    if(chgUiState != chgUiMaintenance)
    {
    	portIOcontrol.EnableLED_ChgGrn();
    	portIOcontrol.DisableLED_ChgAmb();
        chgUiState = chgUiMaintenance;
    }
}
void setChgLedsErrorSulfated()   //Red and green flash once per 5s
{
    if(chgUiState != chgUiErrSulfated)
    {
        blinkIndex = 0;
        setChgLedsOff();
        chgUiState = chgUiErrSulfated;
    }
}
void setChgLedsErrorRecovTimeout()   //Red and green flash twice per 5s
{
    if(chgUiState != chgUiErrRecovTimeout)
    {
        blinkIndex = 0;
        setChgLedsOff();
        chgUiState = chgUiErrRecovTimeout;
    }
}
void setChgLedsErrorCCTimeout()   //Red and green flash three times per 5s
{
    if(chgUiState != chgUiErrCCTimeout)
    {
        blinkIndex = 0;
        setChgLedsOff();
        chgUiState = chgUiErrCCTimeout;
    }
}
void setJumpLedsWaitForBattery()  //Flashing green
{
    if(jmpUiState != jmpUiWaitingForBattery)
    {
        setJumpLedsOff();
        jmpUiState = jmpUiWaitingForBattery;
    }
}
void setJumpLedsJumping()   //Solid green
{
    if(jmpUiState != jmpUiJumping)
    {
    	portIOcontrol.EnableLED_JmpGrn();
    	portIOcontrol.DisableLED_JmpAmb();
        jmpUiState = jmpUiJumping;
    }
}
void setJumpLedsFinshdJumping()   //Solid red
{
    if(jmpUiState != jmpUiFinishedJumping)
    {
    	portIOcontrol.EnableLED_JmpAmb();
    	portIOcontrol.DisableLED_JmpGrn();
        jmpUiState = jmpUiFinishedJumping;
    }
}
void setJumpLedsCellpackError()   //Flashing red
{
    if(jmpUiState != jmpUiCellpackError)
    {
        setJumpLedsOff();
        jmpUiState = jmpUiCellpackError;
    }
}
void setLedsErrorPolarity()    //Red/Green opposed flashing
{
    if(generalUiErrorState != generalUiErrorPolarity)
    {
    	portIOcontrol.DisableLED_ALL();
    	portIOcontrol.EnableLED_ChgAmb();
        generalUiErrorState = generalUiErrorPolarity;
    }
}
void setLedsAcJumpContention()   //Both reds blinking indicate jump cable plugged in while also plugged into AC
{
    if(generalUiErrorState != generalUiErrorAcJumpContention)
    {
        setLedsAllOff();
        generalUiErrorState = generalUiErrorAcJumpContention;
    }
}
void setLedsLowCellpack()    //Pulse red every 4s
{
    if(generalUiErrorState != generalUiErrorLowCellpack)
    {
        blinkIndex = 0;
        setLedsAllOff();
        generalUiErrorState = generalUiErrorLowCellpack;
    }
}
