/*
 * batterycharging.h
 *
 *  Created on: Dec 13, 2021
 *      Author: peters
 */

#ifndef GENERAL_CHARGING_BATTERYCHARGING_H_
#define GENERAL_CHARGING_BATTERYCHARGING_H_

#include "main.h"
#include "../General/charging/portbatterycharging.h"
#include "../General/hw_interfaces/ioControl.h"

//#define CHGTYPE_CURRENTCONTROL
#define CHGTYPE_PULSE

typedef enum
{
    nominalBatteryV_6,
    nominalBatteryV_12,
    nominalBatteryV_24,
    nominalBatteryV_36,
    nominalBatteryV_48
} batterynominalvoltage_t;

typedef enum
{
    batteryChemistry_AGM,
    batteryChemistry_GEL,
    batteryChemistry_LiFePO,
    batteryChemistry_STD
} batterychemistry_t;

#if defined(CHGTYPE_CURRENTCONTROL)
typedef struct
{
    batterychemistry_t batteryChemistry;
    batterynominalvoltage_t batteryNominalVoltage;
    uint16_t batteryConstantCurrent_mA;
    uint32_t timeSinceChargingStart_sec;
    uint16_t batteryDetectionLevel_mV;
    uint16_t batteryRecoveryLevel1_mV;
    uint16_t batteryRecoveryLevel2_mV;
    uint16_t batteryRecoveryCurrent1_mA;
    uint16_t batteryRecoveryCurrent2_mA;
    uint32_t batteryRecoveryPeriod1_sec;
    uint32_t batteryRecoveryPeriod2_sec;
    uint32_t timeSinceRecoveryStart;
    uint16_t batteryCCThreshold_mV;
    uint16_t batteryCCOutput_mV;
    uint16_t batteryReturnFromCV2CCThreshold_mV;
    uint32_t batteryCCMaxTime_sec;
    uint32_t timeSinceCCStart_sec;
    uint16_t batteryCCRestartThreshold_mV;
    uint16_t batteryCVOutput_mV;
    uint32_t batteryCVPeriod_sec;
    uint32_t batteryCVMaxTime_sec;
    uint32_t timeSinceCVStart_sec;
    uint16_t batteryMaintenanceOutput_mV;
} batterychargeparameters_t;
#elif defined(CHGTYPE_PULSE)
typedef struct
{
    batterychemistry_t batteryChemistry;
    batterynominalvoltage_t batteryNominalVoltage;
    uint16_t batteryConstantCurrent_mA;
    uint32_t timeSinceChargingStart_sec;
    uint16_t batteryDetectionLevel_mV;
    uint16_t batteryRecoveryLevel1_mV;
    uint16_t batteryRecoveryLevel2_mV;
    uint32_t batteryRecoveryPeriod1_sec;
    uint32_t batteryRecoveryPeriod2_sec;
    uint32_t timeSinceRecoveryStart;
    uint16_t batteryCCThreshold_mV;
    uint16_t batteryReturnFromCV2CCThreshold_mV;
    uint32_t batteryCCMaxTime_sec;
    uint32_t timeSinceCCStart_sec;
    uint16_t batteryCCRestartThreshold_mV;
    uint32_t batteryCVPeriod_sec;
    uint32_t batteryCVMaxTime_sec;
    uint32_t timeSinceCVStart_sec;
    uint16_t batteryMaintenanceOutput_mV;
} batterychargeparameters_t;
#endif

typedef enum
{
    stateBatteryChargeStopCharging,
    stateBatteryChargeWaitForBattery,
    stateBatteryChargeStart,
    stateBatteryChargeRecovery,
    stateBatteryChargeConstantCurrent,
    stateBatteryChargeConstantVoltage,
    stateBatteryChargeMaintenance,
    stateBatteryChargeReversePolarity,
    stateBatteryChargeSulfated,
    stateBatteryChargeRecoveryTimeout,
    stateBatteryChargeCCTimeout,
    stateBatteryChargeExit
} batterychargestate_t;

void AssertstateBatteryChargeStopCharging(void);
void DeassertstateBatteryChargeStopCharging(void);

void resetBatteryChargeStateMachine(batterychargeparameters_t *battParamIn, charger_t *charger);
void setBatteryMeasureFn(uint8_t chargePath);
batterychargestate_t batteryChargeStateMachine(void);

#endif /* GENERAL_CHARGING_BATTERYCHARGING_H_ */
