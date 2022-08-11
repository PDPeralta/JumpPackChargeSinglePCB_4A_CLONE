/*
 * ioControl.h
 *
 *  Created on: Jul 29, 2022
 *      Author: paulp
 */

#include "../Platform_Specific/hwPortFunctions.h"

#ifndef HW_INTERFACES_IOCONTROL_H_
#define HW_INTERFACES_IOCONTROL_H_

void JumpRelay_Enable();
void JumpRelay_Disable();
void ExtBatt_ChgPathEnable();
void ExtBatt_ChgPathDisable();
void IntBattAC_ChgPathEnable();
void IntBattAC_ChgPathDisable();
void IntBattUSB_ChgPathEnable();
void IntBattUSB_ChgPathDisable();
void USBAccChgPathEnable();
void USBAccChgPathDisable();
void Detected_ACPower();
void Pressed_ChemSelButton();
void Detected_USBPowerInput();
void PluggedIn_JumpCable();

void EnableLED_Lithium();
void DisableLED_Lithium();
void EnableLED_Agm();
void DisableLED_Agm();
void EnableLED_JmpAmb();
void DisableLED_JmpAmb();
void toggleLED_JmpAmb();
void EnableLED_JmpGrn();
void DisableLED_JmpGrn();
void toggleLED_JmpGrn();
void EnableLED_ChgAmb();
void DisableLED_ChgAmb();
void toggleLED_ChgAmb();
void EnableLED_ChgGrn();
void DisableLED_ChgGrn();
void toggleLED_ChgGrn();
void EnableLED_Light();
void DisableLED_Light();
void EnableLED_SOC1();
void DisableLED_SOC1();
void EnableLED_SOC2();
void DisableLED_SOC2();
void EnableLED_SOC3();
void DisableLED_SOC3();
void EnableLED_SOC4();
void DisableLED_SOC4();
void EnableLED_SOC5();
void DisableLED_SOC5();
void EnableLED_ALL();
void DisableLED_ALL();
void toggleLED_ALL();
void XfrmCtrl_Enable();
void XfrmCtrl_Disable();
void AutoForce1_Enable();
void AutoForce1_Disable();
void AutoForce2_Enable();
void AutoForce2_Disable();

typedef struct iocontrol
{
void(*JumpRelay_Enable)();
void(*JumpRelay_Disable)();
void(*ExtBatt_ChgPathEnable)();
void(*ExtBatt_ChgPathDisable)();
void(*IntBattAC_ChgPathEnable)();
void(*IntBattAC_ChgPathDisable)();
void(*IntBattUSB_ChgPathEnable)();
void(*IntBattUSB_ChgPathDisable)();
void(*USBAccChgPathEnable)();
void(*USBAccChgPathDisable)();
void(*EnableLED_Lithium)();
void(*DisableLED_Lithium)();
void(*EnableLED_Agm)();
void(*DisableLED_Agm)();
void(*EnableLED_JmpAmb)();
void(*DisableLED_JmpAmb)();
void(*ToggleLED_JmpAmb)();
void(*EnableLED_JmpGrn)();
void(*DisableLED_JmpGrn)();
void(*ToggleLED_JmpGrn)();
void(*EnableLED_ChgAmb)();
void(*DisableLED_ChgAmb)();
void(*ToggleLED_ChgAmb)();
void(*EnableLED_ChgGrn)();
void(*DisableLED_ChgGrn)();
void(*ToggleLED_ChgGrn)();
void(*EnableLED_Light)();
void(*DisableLED_Light)();
void(*EnableLED_SOC1)();
void(*DisableLED_SOC1)();
void(*EnableLED_SOC2)();
void(*DisableLED_SOC2)();
void(*EnableLED_SOC3)();
void(*DisableLED_SOC3)();
void(*EnableLED_SOC4)();
void(*DisableLED_SOC4)();
void(*EnableLED_SOC5)();
void(*DisableLED_SOC5)();
void(*EnableLED_ALL)();
void(*DisableLED_ALL)();
void(*ToggleLED_ALL)();
void(*XfrmCtrl_Enable)();
void(*XfrmCtrl_Disable)();
void(*AutoForce1_Enable)();
void(*AutoForce1_Disable)();
void(*AutoForce2_Enable)();
void(*AutoForce2_Disable)();

uint8_t(*Detected_ACPower)();
uint8_t(*Pressed_ChemSelButton)();
uint8_t(*Detected_USBPowerInput)();
uint8_t(*PluggedIn_JumpCable)();
} iocontrol_t;

extern iocontrol_t portIOcontrol;


#endif /* HW_INTERFACES_IOCONTROL_H_ */
