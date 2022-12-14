/*
 * ioControl.c
 *
 *  Created on: Jul 29, 2022
 *      Author: paulp
 */

#include "../General/hw_interfaces/ioControl.h"

iocontrol_t portIOcontrol = { .JumpRelay_Enable = CloseJumpRelay,
							 .JumpRelay_Disable = OpenJumpRelay,
							 .ExtBatt_ChgPathEnable = EnableExtBattChgPath,
							 .ExtBatt_ChgPathDisable = DisableExtBattChgPath,
							 .IntBattAC_ChgPathEnable = EnableACIntBattChgPath,
							 .IntBattAC_ChgPathDisable = DisableACIntBattChgPath,
							 .IntBattUSB_ChgPathEnable = EnableUSBIntBattChgPath,
							 .IntBattUSB_ChgPathDisable = DisableUSBIntBattChgPath,
							 .USBAccChgPathEnable = EnableUSBAccChgPath,
							 .USBAccChgPathDisable = DisableUSBAccChgPath,
							 .Detected_ACPower = ACPowerDetected,
							 .Pressed_ChemSelButton = ChemSelButtonPressed,
							 .Detected_USBPowerInput = USBPowerInputDetected,
							 .PluggedIn_JumpCable = JumpCablePluggedIn,
							 .EnableLED_Lithium = setLED_Lithium,
							 .DisableLED_Lithium = clrLED_Lithium,
							 .EnableLED_Agm = setLED_Agm,
							 .DisableLED_Agm = clrLED_Agm,
							 .EnableLED_JmpAmb = setLED_JmpAmb,
							 .DisableLED_JmpAmb = clrLED_JmpAmb,
							 .ToggleLED_JmpAmb = toggleLED_JmpAmb,
							 .EnableLED_JmpGrn = setLED_JmpGrn,
							 .DisableLED_JmpGrn = clrLED_JmpGrn,
							 .ToggleLED_JmpGrn = toggleLED_JmpGrn,
							 .EnableLED_ChgAmb = setLED_ChgAmb,
							 .DisableLED_ChgAmb = clrLED_ChgAmb,
							 .ToggleLED_ChgAmb = toggleLED_ChgAmb,
							 .EnableLED_ChgGrn = setLED_ChgGrn,
							 .DisableLED_ChgGrn = clrLED_ChgGrn,
							 .ToggleLED_ChgGrn = toggleLED_ChgGrn,
							 .EnableLED_Light = setLED_Light,
							 .DisableLED_Light = clrLED_Light,
							 .EnableLED_SOC1 = setLED_SOC1,
							 .DisableLED_SOC1 = clrLED_SOC1,
							 .EnableLED_SOC2 = setLED_SOC2,
							 .DisableLED_SOC2 = clrLED_SOC2,
							 .EnableLED_SOC3 = setLED_SOC3,
							 .DisableLED_SOC3 = clrLED_SOC3,
							 .EnableLED_SOC4 = setLED_SOC4,
							 .DisableLED_SOC4 = clrLED_SOC4,
							 .EnableLED_SOC5 = setLED_SOC5,
							 .DisableLED_SOC5 = clrLED_SOC5,
							 .EnableLED_ALL = setLED_ALL,
							 .DisableLED_ALL = clrLED_ALL,
							 .ToggleLED_ALL = toggleLED_ALL,
							 .XfrmCtrl_Enable = enable_XfrmCtrl,
							 .XfrmCtrl_Disable = disable_XfrmCtrl,
							 .AutoForce1_Enable = closeFET_AutoForce1,
							 .AutoForce1_Disable = openFET_AutoForce1,
							 .AutoForce1_Enable = closeFET_AutoForce2,
							 .AutoForce1_Disable = openFET_AutoForce2,
							};
