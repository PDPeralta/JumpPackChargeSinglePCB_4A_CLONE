/*
 * led_indication.h
 *
 *  Created on: Apr 8, 2022
 *      Author: tjose
 */

#ifndef GENERAL_LED_INDICATION_LED_INDICATION_H_
#define GENERAL_LED_INDICATION_LED_INDICATION_H_


//Functions for setting multiple LEDs according to the state
void setLedsErrUncalibrated();
void setLedsCalSuccess();
void doLedTestSequence();
void setLedsAllOn();
void setLedsAllOff();
void setJumpLedsOff();
void setChgLedsOff();
void setChemistryLeds(int lithiumLed, int agmLed);
void setChgLedsWaitForBattery();
void setChgLedsCharging();
void setChgLedsConstantVoltage();
void setChgLedsMaintenance();
void setChgLedsErrorSulfated();
void setChgLedsErrorRecovTimeout();
void setChgLedsErrorCCTimeout();
void setJumpLedsWaitForBattery();
void setJumpLedsJumping();
void setJumpLedsFinshdJumping();
void setJumpLedsCellpackError();
void setLedsErrorPolarity();
void setLedsAcJumpContention();
void setLedsLowCellpack();
void setCellpackChgLevelIndication(int cpack_mV);

void tickLedMachine();


#endif /* GENERAL_LED_INDICATION_LED_INDICATION_H_ */
