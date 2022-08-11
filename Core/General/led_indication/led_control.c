/*
 * led_control.c
 *
 *  Created on: Aug 1, 2022
 *      Author: paulp
 */

#include "../General/led_indication/led_control.h"

void setLedChemistryAgm()
{
	portIOcontrol.DisableLED_Lithium();
	portIOcontrol.EnableLED_Agm();
}
void setLedChemistryLith()
{
	portIOcontrol.DisableLED_Agm();
	portIOcontrol.EnableLED_Lithium();
}
void setLedChgRed(uint8_t state)
{
    if(state)
    {
    	portIOcontrol.EnableLED_ChgAmb();
    }
    else
    {
    	portIOcontrol.DisableLED_ChgAmb();
    }
}
void toggleLedChgRed()
{
	portIOcontrol.ToggleLED_ChgAmb();
}
void setLedChgGrn(uint8_t state)
{
    if(state)
    {
    	portIOcontrol.EnableLED_ChgGrn();
    }
    else
    {
    	portIOcontrol.DisableLED_ChgGrn();
    }
}
void toggleLedChgGrn()
{
	portIOcontrol.ToggleLED_ChgGrn();
}
void setLedJumpRed(uint8_t state)
{
    if(state)
    {
    	portIOcontrol.EnableLED_JmpAmb();
    }
    else
    {
    	portIOcontrol.DisableLED_JmpAmb();
    }
}
void toggleLedJumpRed()
{
	portIOcontrol.ToggleLED_JmpAmb();
}
void setLedJumpGrn(uint8_t state)
{
    if(state)
    {
    	portIOcontrol.EnableLED_JmpGrn();
    }
    else
    {
    	portIOcontrol.DisableLED_JmpGrn();
    }
}
void toggleLedJumpGrn()
{
	portIOcontrol.ToggleLED_JmpGrn();
}


void setLedsStateOfCellpack(uint8_t numOn)   //Argument is number one out of 5
{
    switch(numOn)
    {
    case 1:
    	portIOcontrol.EnableLED_SOC1();
    	portIOcontrol.DisableLED_SOC2();
    	portIOcontrol.DisableLED_SOC3();
    	portIOcontrol.DisableLED_SOC4();
    	portIOcontrol.DisableLED_SOC5();
        break;
    case 2:
    	portIOcontrol.EnableLED_SOC1();
    	portIOcontrol.EnableLED_SOC2();
    	portIOcontrol.DisableLED_SOC3();
    	portIOcontrol.DisableLED_SOC4();
    	portIOcontrol.DisableLED_SOC5();
        break;
    case 3:
    	portIOcontrol.EnableLED_SOC1();
    	portIOcontrol.EnableLED_SOC2();
    	portIOcontrol.EnableLED_SOC3();
    	portIOcontrol.DisableLED_SOC4();
    	portIOcontrol.DisableLED_SOC5();
        break;
    case 4:
    	portIOcontrol.EnableLED_SOC1();
    	portIOcontrol.EnableLED_SOC2();
    	portIOcontrol.EnableLED_SOC3();
    	portIOcontrol.EnableLED_SOC4();
    	portIOcontrol.DisableLED_SOC5();
        break;
    case 5:
    	portIOcontrol.EnableLED_SOC1();
    	portIOcontrol.EnableLED_SOC2();
    	portIOcontrol.EnableLED_SOC3();
    	portIOcontrol.EnableLED_SOC4();
    	portIOcontrol.EnableLED_SOC5();
        break;

    default:
        break;
    }

}


void setLedLight(uint8_t state)
{
    if(state)
    {
    	portIOcontrol.EnableLED_Light();
    }
    else
    {
    	portIOcontrol.DisableLED_Light();
    }
}
void setTransformerEnable(uint8_t state)
{
    if(state)
    {
    	portIOcontrol.XfrmCtrl_Enable();
    }
    else
    {
    	portIOcontrol.XfrmCtrl_Disable();
    }
}

// create an enumerated type for which auto force mode you want to be in.
// and then use this function to take in that argument and set the GPIO's accordingly
// make the function into a switch statement, one case for each auto_force mode
void setAutoforceFETs(AutoForceState_t level)
{
    switch(level)
    {
    case 0:
    	portIOcontrol.AutoForce1_Disable();
    	portIOcontrol.AutoForce2_Disable();
    	break;

    case 1:
    	portIOcontrol.AutoForce1_Enable();
    	portIOcontrol.AutoForce2_Disable();
    	break;

    case 2:
    	portIOcontrol.AutoForce1_Disable();
    	portIOcontrol.AutoForce2_Enable();
    	break;

    case 3:
    	portIOcontrol.AutoForce1_Enable();
    	portIOcontrol.AutoForce2_Enable();
    	break;

    default:
    	break;
    }
}
