/*
 * delay_lowpower.h
 *
 *  Created on: Apr 7, 2022
 *      Author: tjose
 */

#ifndef GENERAL_DELAY_LOWPOWER_DELAY_LOWPOWER_H_
#define GENERAL_DELAY_LOWPOWER_DELAY_LOWPOWER_H_

#define RTC_CLOCKSPEED_HZ        10000   //40KHz LSI clock with DIV4 setting in RTC peripheral

void delay_lowpower(int delayMs);
void goLowPowerState();

#endif /* GENERAL_DELAY_LOWPOWER_DELAY_LOWPOWER_H_ */
