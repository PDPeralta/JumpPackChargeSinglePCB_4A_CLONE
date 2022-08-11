/*
 * bulkPWM.c
 *
 *  Created on: Jan 4, 2022
 *      Author: tjose
 */
#include "../Platform_Specific/chargePWM.h"

extern TIM_HandleTypeDef htim3;

#define MIN_ALLOWED_PWM_FREQ_HZ    200
#define MAX_ALLOWED_PWM_FREQ_HZ    10000
#define DEFAULT_PWM_FREQ_HZ        500
static uint32_t autoReloadValue = 0; //Auto reload register determines the period of the PWM pulse. See ST RM0366 section 19.4.10

static uint32_t GetTIMPCLK(void);

void pwmConfigFrequency(uint16_t freq)
{
    if (freq < MIN_ALLOWED_PWM_FREQ_HZ || freq > MAX_ALLOWED_PWM_FREQ_HZ)
    {
        freq = DEFAULT_PWM_FREQ_HZ;
    }
    uint32_t timerClkFreq = GetTIMPCLK();
    autoReloadValue = timerClkFreq / freq;
    htim3.Channel = HAL_TIM_ACTIVE_CHANNEL_1;
    __HAL_TIM_SET_AUTORELOAD(&htim3, autoReloadValue);
    htim3.Channel = HAL_TIM_ACTIVE_CHANNEL_2;
    __HAL_TIM_SET_AUTORELOAD(&htim3, autoReloadValue);
    htim3.Channel = HAL_TIM_ACTIVE_CHANNEL_CLEARED;
}

uint32_t PWM_Get100PercentValue()
{
    return autoReloadValue + 1;
}

void PWM_Bulk_Start()
{
    HAL_TIM_Base_Start(&htim3);                  //Start TIM17 base generation
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);    //Start PWM Output
}
void PWM_Bulk_Stop()
{
    HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_2);    //Stop PWM Output
    HAL_TIM_Base_Stop(&htim3);                  //Stop TIM17 base generation
}
void PWM_Bulk_SetDutycycle(uint8_t dutycycle)
{
    if (autoReloadValue == 0) //In case pwmConfigFrequency() wasn't called first, configure autoreload for default frequency
    {
        uint32_t timerClkFreq = GetTIMPCLK();
        autoReloadValue = timerClkFreq / DEFAULT_PWM_FREQ_HZ;
        htim3.Channel = HAL_TIM_ACTIVE_CHANNEL_2;
        __HAL_TIM_SET_AUTORELOAD(&htim3, autoReloadValue);
        htim3.Channel = HAL_TIM_ACTIVE_CHANNEL_CLEARED;
    }
    //Convert PWM Pulse in percentage to DN
    uint32_t ccvalue = ((dutycycle * autoReloadValue) / 100); //Auto reload register determines the period of the PWM pulse. See ST RM0366 section 19.4.10
    if (dutycycle >= 100)
    {
        ccvalue = autoReloadValue + 1; //If capture compare > auto reload value, PWM output will be held at 1 (100% dutycycle)
    }
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, ccvalue); //Set Pulse Width / CC1 value
}

void PWM_CC_Start()
{
    HAL_TIM_Base_Start(&htim3);                  //Start TIM17 (constant current control) time base generation
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);    //Start PWM Output
}
void PWM_CC_Stop()
{
    HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_2);    //Stop PWM Output
    HAL_TIM_Base_Stop(&htim3);
}
void PWM_CC_SetDN(uint32_t DN)
{
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, DN);
}

void PWM_CC_SetmA(uint16_t mA)
{
    uint32_t Vout = 0;
    uint32_t DNout = 0;

    //Pull these from parameters, should not be hard coded
    //15 = milli-ohmm current sense resistor
    //40 = ADCI op amp gain
    //1000 = full scale of PWM I
    //3300 = full scale of I/O
    Vout = (15 * mA * 45)/1000;
    DNout = (1000 * Vout)/3300;

    PWM_CC_SetDN(DNout);
}

void PWM_CV_Start()
{
    HAL_TIM_Base_Start(&htim3);                  //Start TIM16 (constant voltage control) time base generation
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);    //Start PWM Output
}
void PWM_CV_Stop()
{
    HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);    //Stop PWM Output
    HAL_TIM_Base_Stop(&htim3);
}
void PWM_CV_SetDN(uint32_t DN)
{
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, DN);
}

static uint32_t GetTIMPCLK(void)
{
	  uint32_t bigint=0;
	  uint32_t APBprescaler=1;
	  uint32_t TIMPCLK = 0;
	  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

	  HAL_RCC_GetClockConfig(&RCC_ClkInitStruct, &bigint);
	  if (RCC_ClkInitStruct.APB1CLKDivider == RCC_APB1_DIV1)
	  {
		  APBprescaler = 1;
	  }
	  else
	  {
		  APBprescaler = 2;
	  }
	  bigint = HAL_RCC_GetPCLK1Freq();
	  TIMPCLK = APBprescaler * bigint;

	  return TIMPCLK;
}
