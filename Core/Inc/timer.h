/*
 * timer.h
 *
 *  Created on: Jul 25, 2022
 *      Author: paulp
 */

#include "main.h"

#include "../General/led_indication/led_indication.h"

#ifndef INC_TIMER_H_
#define INC_TIMER_H_

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
void resetSecondsElapsed();
uint32_t getSecondsElapsed();

#endif /* INC_TIMER_H_ */
