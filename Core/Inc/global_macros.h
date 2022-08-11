/*
 * tasks_include.h
 *
 *  Created on: Dec 8, 2021
 *      Author: peters
 */

#ifndef APP_TASKS_TASKS_INCLUDE_H_
#define APP_TASKS_TASKS_INCLUDE_H_

//TODO: Move these macros into different header file
//as we don't use tasks anymore

#include "main.h"

#define FLAG_REVPOLARITY             (uint32_t)(1 << 0)
#define FLAG_SULFATED                (uint32_t)(1 << 1)
#define FLAG_RECOVTIMEOUT            (uint32_t)(1 << 2)
#define FLAG_CCTIMEOUT               (uint32_t)(1 << 3)
#define FLAG_JUMP_ERROR              (uint32_t)(1 << 4)
#define FLAG_LOW_BATTERY             (uint32_t)(1 << 5)

#define INTERNAL_BATT_LOW_LEVEL_MV               12500
#define INTERNAL_BATT_ACC_CHARGE_LEVEL_MV        13500
#define INTERNAL_BATT_JUMP_RDY_LEVEL_MV          14000
#define INTERNAL_BATT_MAINTAIN_LEVEL_MV          15000

#define EXT_BATT_JUMP_DET_MV                     2000
#define MAX_JUMP_ATTEMPTS                        7

/*
#define AC_POWER_DETECTED                (HAL_GPIO_ReadPin(AC_DET_GPIO_Port, AC_DET_Pin) == GPIO_PIN_RESET)
#define CHEMSEL_BUTTON_PRESSED           (HAL_GPIO_ReadPin(BTN_SEL_GPIO_Port, BTN_SEL_Pin) == GPIO_PIN_RESET)
#define USB_POWER_IN_DETECTED            (HAL_GPIO_ReadPin(USB_DET_GPIO_Port, USB_DET_Pin) == GPIO_PIN_SET)
#define JUMP_CABLE_PLUGGED_IN            (HAL_GPIO_ReadPin(JUMP_DET_GPIO_Port, JUMP_DET_Pin) == GPIO_PIN_RESET)

#define OPEN_JUMP_RELAY                  HAL_GPIO_WritePin(JUMP_OUT_GPIO_Port, JUMP_OUT_Pin, GPIO_PIN_RESET)
#define CLOSE_JUMP_RELAY                 HAL_GPIO_WritePin(JUMP_OUT_GPIO_Port, JUMP_OUT_Pin, GPIO_PIN_SET)
#define ENABLE_EXTBATT_CHG_PATH          HAL_GPIO_WritePin(CRG_OUT_GPIO_Port, CRG_OUT_Pin, GPIO_PIN_SET)
#define DISABLE_EXTBATT_CHG_PATH         HAL_GPIO_WritePin(CRG_OUT_GPIO_Port, CRG_OUT_Pin, GPIO_PIN_RESET)
#define ENABLE_INTBATT_AC_CHG_PATH       HAL_GPIO_WritePin(CRG_OUT_Int_GPIO_Port, CRG_OUT_Int_Pin, GPIO_PIN_SET)
#define DISABLE_INTBATT_AC_CHG_PATH      HAL_GPIO_WritePin(CRG_OUT_Int_GPIO_Port, CRG_OUT_Int_Pin, GPIO_PIN_RESET)
#define ENABLE_INTBATT_USB_CHG_PATH      HAL_GPIO_WritePin(USB_CHR_EN_GPIO_Port, USB_CHR_EN_Pin, GPIO_PIN_RESET)
#define DISABLE_INTBATT_USB_CHG_PATH     HAL_GPIO_WritePin(USB_CHR_EN_GPIO_Port, USB_CHR_EN_Pin, GPIO_PIN_SET)   //It's enable not, reg is pulled up by default in hw
#define ENABLE_USB_ACCESSORY_CHG         HAL_GPIO_WritePin(ACC_OUT_GPIO_Port, ACC_OUT_Pin, GPIO_PIN_SET)
#define DISABLE_USB_ACCESSORY_CHG        HAL_GPIO_WritePin(ACC_OUT_GPIO_Port, ACC_OUT_Pin, GPIO_PIN_RESET)
*/


#endif /* APP_TASKS_TASKS_INCLUDE_H_ */
