/*
 * hwPortFunctions.c
 *
 *  Created on: Jul 28, 2022
 *      Author: paulp
 */

#include "../Platform_Specific/hwPortFunctions.h"

// Write Pin Functions
void OpenJumpRelay(){
	HAL_GPIO_WritePin(JUMP_OUT_GPIO_Port, JUMP_OUT_Pin, GPIO_PIN_RESET);
	}
void CloseJumpRelay(){
	HAL_GPIO_WritePin(JUMP_OUT_GPIO_Port, JUMP_OUT_Pin, GPIO_PIN_SET);
	}
void EnableExtBattChgPath(){
	HAL_GPIO_WritePin(CRG_OUT_GPIO_Port, CRG_OUT_Pin, GPIO_PIN_SET);
	}
void DisableExtBattChgPath(){
	HAL_GPIO_WritePin(CRG_OUT_GPIO_Port, CRG_OUT_Pin, GPIO_PIN_RESET);
	}
void EnableACIntBattChgPath(){
	HAL_GPIO_WritePin(CRG_OUT_Int_GPIO_Port, CRG_OUT_Int_Pin, GPIO_PIN_SET);
	}
void DisableACIntBattChgPath(){
	HAL_GPIO_WritePin(CRG_OUT_Int_GPIO_Port, CRG_OUT_Int_Pin, GPIO_PIN_RESET);
	}
void EnableUSBIntBattChgPath(){
	HAL_GPIO_WritePin(USB_CHR_EN_GPIO_Port, USB_CHR_EN_Pin, GPIO_PIN_RESET);
	}
void DisableUSBIntBattChgPath(){
	HAL_GPIO_WritePin(USB_CHR_EN_GPIO_Port, USB_CHR_EN_Pin, GPIO_PIN_SET);
	}
void EnableUSBAccChgPath(){
	HAL_GPIO_WritePin(ACC_OUT_GPIO_Port, ACC_OUT_Pin, GPIO_PIN_SET);
	}
void DisableUSBAccChgPath(){
	HAL_GPIO_WritePin(ACC_OUT_GPIO_Port, ACC_OUT_Pin, GPIO_PIN_RESET);
	}
void setLED_Lithium(){
	HAL_GPIO_WritePin(LED_LITH_GPIO_Port, LED_LITH_Pin, GPIO_PIN_SET);
	}
void clrLED_Lithium(){
	HAL_GPIO_WritePin(LED_LITH_GPIO_Port, LED_LITH_Pin, GPIO_PIN_RESET);
	}
void setLED_Agm(){
	HAL_GPIO_WritePin(LED_AGM_GPIO_Port, LED_AGM_Pin, GPIO_PIN_SET);
	}
void clrLED_Agm(){
	HAL_GPIO_WritePin(LED_AGM_GPIO_Port, LED_AGM_Pin, GPIO_PIN_RESET);
	}
void setLED_JmpAmb(){
	HAL_GPIO_WritePin(LED_JMP_AMB_GPIO_Port, LED_JMP_AMB_Pin, GPIO_PIN_SET);
	}
void clrLED_JmpAmb(){
	HAL_GPIO_WritePin(LED_JMP_AMB_GPIO_Port, LED_JMP_AMB_Pin, GPIO_PIN_RESET);
	}
void toggleLED_JmpAmb(){
	HAL_GPIO_TogglePin(LED_JMP_AMB_GPIO_Port, LED_JMP_AMB_Pin);
	}
void setLED_JmpGrn(){
	HAL_GPIO_WritePin(LED_JMP_GRN_GPIO_Port, LED_JMP_GRN_Pin, GPIO_PIN_SET);
	}
void clrLED_JmpGrn(){
	HAL_GPIO_WritePin(LED_JMP_GRN_GPIO_Port, LED_JMP_GRN_Pin, GPIO_PIN_RESET);
	}
void toggleLED_JmpGrn(){
	HAL_GPIO_TogglePin(LED_JMP_GRN_GPIO_Port, LED_JMP_GRN_Pin);
	}
void setLED_ChgAmb(){
	HAL_GPIO_WritePin(LED_CHG_AMB_GPIO_Port, LED_CHG_AMB_Pin, GPIO_PIN_SET);
	}
void clrLED_ChgAmb(){
	HAL_GPIO_WritePin(LED_CHG_AMB_GPIO_Port, LED_CHG_AMB_Pin, GPIO_PIN_RESET);
	}
void toggleLED_ChgAmb(){
	HAL_GPIO_TogglePin(LED_CHG_AMB_GPIO_Port, LED_CHG_AMB_Pin);
	}
void setLED_ChgGrn(){
	HAL_GPIO_WritePin(LED_CHG_GRN_GPIO_Port, LED_CHG_GRN_Pin, GPIO_PIN_SET);
	}
void clrLED_ChgGrn(){
	HAL_GPIO_WritePin(LED_CHG_GRN_GPIO_Port, LED_CHG_GRN_Pin, GPIO_PIN_RESET);
	}
void toggleLED_ChgGrn(){
	HAL_GPIO_TogglePin(LED_CHG_GRN_GPIO_Port, LED_CHG_GRN_Pin);
	}
void setLED_Light(){
	HAL_GPIO_WritePin(LED_LIGHT_GPIO_Port, LED_LIGHT_Pin, GPIO_PIN_SET);
	}
void clrLED_Light(){
	HAL_GPIO_WritePin(LED_LIGHT_GPIO_Port, LED_LIGHT_Pin, GPIO_PIN_RESET);
	}
void setLED_SOC1(){
	HAL_GPIO_WritePin(SOC1_GPIO_Port, SOC1_Pin, GPIO_PIN_SET);
	}
void clrLED_SOC1(){
	HAL_GPIO_WritePin(SOC1_GPIO_Port, SOC1_Pin, GPIO_PIN_RESET);
	}
void setLED_SOC2(){
	HAL_GPIO_WritePin(SOC2_GPIO_Port, SOC2_Pin, GPIO_PIN_SET);
	}
void clrLED_SOC2(){
	HAL_GPIO_WritePin(SOC2_GPIO_Port, SOC2_Pin, GPIO_PIN_RESET);
	}
void setLED_SOC3(){
	HAL_GPIO_WritePin(SOC3_GPIO_Port, SOC3_Pin, GPIO_PIN_SET);
	}
void clrLED_SOC3(){
	HAL_GPIO_WritePin(SOC3_GPIO_Port, SOC3_Pin, GPIO_PIN_RESET);
	}
void setLED_SOC4(){
	HAL_GPIO_WritePin(SOC4_GPIO_Port, SOC4_Pin, GPIO_PIN_SET);
	}
void clrLED_SOC4(){
	HAL_GPIO_WritePin(SOC4_GPIO_Port, SOC4_Pin, GPIO_PIN_RESET);
	}
void setLED_SOC5(){
	HAL_GPIO_WritePin(SOC5_GPIO_Port, SOC5_Pin, GPIO_PIN_SET);
	}
void clrLED_SOC5(){
	HAL_GPIO_WritePin(SOC5_GPIO_Port, SOC5_Pin, GPIO_PIN_RESET);
	}
void setLED_ALL(){
	HAL_GPIO_WritePin(LED_LITH_GPIO_Port, LED_LITH_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED_AGM_GPIO_Port, LED_AGM_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED_JMP_AMB_GPIO_Port, LED_JMP_AMB_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED_JMP_GRN_GPIO_Port, LED_JMP_GRN_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED_CHG_AMB_GPIO_Port, LED_CHG_AMB_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED_CHG_GRN_GPIO_Port, LED_CHG_GRN_Pin, GPIO_PIN_SET);
}
void clrLED_ALL(){
	HAL_GPIO_WritePin(LED_LITH_GPIO_Port, LED_LITH_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LED_AGM_GPIO_Port, LED_AGM_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LED_JMP_AMB_GPIO_Port, LED_JMP_AMB_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LED_JMP_GRN_GPIO_Port, LED_JMP_GRN_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LED_CHG_AMB_GPIO_Port, LED_CHG_AMB_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LED_CHG_GRN_GPIO_Port, LED_CHG_GRN_Pin, GPIO_PIN_RESET);
}
void toggleLED_ALL(){
	HAL_GPIO_TogglePin(LED_LITH_GPIO_Port, LED_LITH_Pin);
	HAL_GPIO_TogglePin(LED_AGM_GPIO_Port, LED_AGM_Pin);
	HAL_GPIO_TogglePin(LED_JMP_AMB_GPIO_Port, LED_JMP_AMB_Pin);
	HAL_GPIO_TogglePin(LED_JMP_GRN_GPIO_Port, LED_JMP_GRN_Pin);
	HAL_GPIO_TogglePin(LED_CHG_AMB_GPIO_Port, LED_CHG_AMB_Pin);
	HAL_GPIO_TogglePin(LED_CHG_GRN_GPIO_Port, LED_CHG_GRN_Pin);
}
void enable_XfrmCtrl(){
	HAL_GPIO_WritePin(XFRM_CTRL_GPIO_Port, XFRM_CTRL_Pin, GPIO_PIN_SET);
	}
void disable_XfrmCtrl(){
	HAL_GPIO_WritePin(XFRM_CTRL_GPIO_Port, XFRM_CTRL_Pin, GPIO_PIN_RESET);
	}
void closeFET_AutoForce1(){
	HAL_GPIO_WritePin(AUTO_Force1_GPIO_Port, AUTO_Force1_Pin, GPIO_PIN_SET);
}
void openFET_AutoForce1(){
	HAL_GPIO_WritePin(AUTO_Force1_GPIO_Port, AUTO_Force1_Pin, GPIO_PIN_RESET);
}
void closeFET_AutoForce2(){
	HAL_GPIO_WritePin(AUTO_Force2_GPIO_Port, AUTO_Force2_Pin, GPIO_PIN_SET);
}
void openFET_AutoForce2(){
	HAL_GPIO_WritePin(AUTO_Force2_GPIO_Port, AUTO_Force2_Pin, GPIO_PIN_RESET);
}


// Read Pin Functions
uint8_t ACPowerDetected(){
	return (HAL_GPIO_ReadPin(AC_DET_GPIO_Port, AC_DET_Pin) == GPIO_PIN_RESET);
	}
uint8_t ChemSelButtonPressed(){
	return (HAL_GPIO_ReadPin(BTN_SEL_GPIO_Port, BTN_SEL_Pin) == GPIO_PIN_RESET);
	}
uint8_t USBPowerInputDetected(){
	return (HAL_GPIO_ReadPin(USB_DET_GPIO_Port, USB_DET_Pin) == GPIO_PIN_SET);
	}
uint8_t JumpCablePluggedIn(){
	return (HAL_GPIO_ReadPin(JUMP_DET_GPIO_Port, JUMP_DET_Pin) == GPIO_PIN_RESET);
	}


