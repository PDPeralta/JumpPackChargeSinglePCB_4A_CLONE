/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32c0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define SOC5_Pin GPIO_PIN_13
#define SOC5_GPIO_Port GPIOC
#define LED_LITH_Pin GPIO_PIN_14
#define LED_LITH_GPIO_Port GPIOC
#define LED_AGM_Pin GPIO_PIN_15
#define LED_AGM_GPIO_Port GPIOC
#define BTN_LIGHT_Pin GPIO_PIN_3
#define BTN_LIGHT_GPIO_Port GPIOF
#define BTN_RST_Pin GPIO_PIN_2
#define BTN_RST_GPIO_Port GPIOF
#define CPAC_TEMP_Pin GPIO_PIN_0
#define CPAC_TEMP_GPIO_Port GPIOA
#define PCBA_TEMP_Pin GPIO_PIN_1
#define PCBA_TEMP_GPIO_Port GPIOA
#define ADC_V_Pin GPIO_PIN_2
#define ADC_V_GPIO_Port GPIOA
#define ADC_I_Pin GPIO_PIN_3
#define ADC_I_GPIO_Port GPIOA
#define ADC_USB_I_Pin GPIO_PIN_4
#define ADC_USB_I_GPIO_Port GPIOA
#define BATT_ADC_Pin GPIO_PIN_5
#define BATT_ADC_GPIO_Port GPIOA
#define LED_JMP_AMB_Pin GPIO_PIN_7
#define LED_JMP_AMB_GPIO_Port GPIOA
#define LED_JMP_GRN_Pin GPIO_PIN_0
#define LED_JMP_GRN_GPIO_Port GPIOB
#define LED_CHG_AMB_Pin GPIO_PIN_1
#define LED_CHG_AMB_GPIO_Port GPIOB
#define LED_CHG_GRN_Pin GPIO_PIN_2
#define LED_CHG_GRN_GPIO_Port GPIOB
#define BTN_SEL_Pin GPIO_PIN_10
#define BTN_SEL_GPIO_Port GPIOB
#define LED_LIGHT_Pin GPIO_PIN_11
#define LED_LIGHT_GPIO_Port GPIOB
#define XFRM_CTRL_Pin GPIO_PIN_12
#define XFRM_CTRL_GPIO_Port GPIOB
#define AUTO_Force2_Pin GPIO_PIN_13
#define AUTO_Force2_GPIO_Port GPIOB
#define AUTO_Force1_Pin GPIO_PIN_14
#define AUTO_Force1_GPIO_Port GPIOB
#define JUMP_DET_Pin GPIO_PIN_15
#define JUMP_DET_GPIO_Port GPIOB
#define PWMV_Pin GPIO_PIN_6
#define PWMV_GPIO_Port GPIOC
#define PWMI_Pin GPIO_PIN_7
#define PWMI_GPIO_Port GPIOC
#define REV_POL_Pin GPIO_PIN_10
#define REV_POL_GPIO_Port GPIOA
#define SOC1_Pin GPIO_PIN_11
#define SOC1_GPIO_Port GPIOA
#define SOC2_Pin GPIO_PIN_12
#define SOC2_GPIO_Port GPIOA
#define JUMP_OUT_Pin GPIO_PIN_15
#define JUMP_OUT_GPIO_Port GPIOA
#define AC_DET_Pin GPIO_PIN_0
#define AC_DET_GPIO_Port GPIOD
#define CRG_OUT_Int_Pin GPIO_PIN_1
#define CRG_OUT_Int_GPIO_Port GPIOD
#define CRG_OUT_Pin GPIO_PIN_2
#define CRG_OUT_GPIO_Port GPIOD
#define ACC_OUT_Pin GPIO_PIN_3
#define ACC_OUT_GPIO_Port GPIOD
#define USB_CHR_EN_Pin GPIO_PIN_3
#define USB_CHR_EN_GPIO_Port GPIOB
#define USB_DET_Pin GPIO_PIN_4
#define USB_DET_GPIO_Port GPIOB
#define SOC4_Pin GPIO_PIN_5
#define SOC4_GPIO_Port GPIOB
#define SOC3_Pin GPIO_PIN_6
#define SOC3_GPIO_Port GPIOB
#define BTN_WAKE_Pin GPIO_PIN_7
#define BTN_WAKE_GPIO_Port GPIOB
#define BTN_WAKE_EXTI_IRQn EXTI4_15_IRQn
#define SCL_Pin GPIO_PIN_8
#define SCL_GPIO_Port GPIOB
#define SDA_Pin GPIO_PIN_9
#define SDA_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
