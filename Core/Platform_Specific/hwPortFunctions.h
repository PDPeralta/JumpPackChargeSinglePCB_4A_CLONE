/*
 * hwPortFunctions.h
 *
 *  Created on: Jul 28, 2022
 *      Author: paulp
 */

#include "main.h"

#ifndef HW_INTERFACES_HWPORTFUNCTIONS_H_
#define HW_INTERFACES_HWPORTFUNCTIONS_H

//Write Pin Functions
void OpenJumpRelay();
void CloseJumpRelay();
void EnableExtBattChgPath();
void DisableExtBattChgPath();
void EnableACIntBattChgPath();
void DisableACIntBattChgPath();
void EnableUSBIntBattChgPath();
void DisableUSBIntBattChgPath();
void EnableUSBAccChgPath();
void DisableUSBAccChgPath();

void setLED_Lithium();
void clrLED_Lithium();
void setLED_Agm();
void clrLED_Agm();
void setLED_JmpAmb();
void clrLED_JmpAmb();
void toggleLED_JmpAmb();
void setLED_JmpGrn();
void clrLED_JmpGrn();
void toggleLED_JmpGrn();
void setLED_ChgAmb();
void clrLED_ChgAmb();
void toggleLED_ChgAmb();
void setLED_ChgGrn();
void clrLED_ChgGrn();
void toggleLED_ChgGrn();
void setLED_Light();
void clrLED_Light();
void setLED_SOC1();
void clrLED_SOC1();
void setLED_SOC2();
void clrLED_SOC2();
void setLED_SOC3();
void clrLED_SOC3();
void setLED_SOC4();
void clrLED_SOC4();
void setLED_SOC5();
void clrLED_SOC5();
void setLED_ALL();
void clrLED_ALL();
void enable_XfrmCtrl();
void disable_XfrmCtrl();
void closeFET_AutoForce1();
void openFET_AutoForce1();
void closeFET_AutoForce2();
void openFET_AutoForce2();


//Read Pin Functions
uint8_t ACPowerDetected();
uint8_t ChemSelButtonPressed();
uint8_t USBPowerInputDetected();
uint8_t JumpCablePluggedIn();


#endif /* HW_INTERFACES_HWPORTFUNCTIONS_H_ */
