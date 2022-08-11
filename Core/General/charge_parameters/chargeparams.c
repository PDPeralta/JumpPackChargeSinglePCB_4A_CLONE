/*
 * chargeparams.c
 *
 *  Created on: Jan 5, 2022
 *      Author: tjose
 */
#include "../General/charge_parameters/chargeparams.h"

battchemistry_t selectedChemistry = StdAgmChemistry;

batterychargeparameters_t StdAgmChargeParameters =
{
    .batteryChemistry = batteryChemistry_AGM,
    .batteryNominalVoltage = nominalBatteryV_12,
    .batteryConstantCurrent_mA = 1000,
    .batteryDetectionLevel_mV = 2000,
    .batteryRecoveryLevel1_mV = 6000,
    .batteryRecoveryLevel2_mV = 8000,
    .batteryRecoveryPeriod1_sec = 120,   //2 minutes
    .batteryRecoveryPeriod2_sec = 300,  //5 minutes
    .batteryCCThreshold_mV = 14600,
    .batteryReturnFromCV2CCThreshold_mV = 14000,
    .batteryCCMaxTime_sec = 259200,      //72hrs "bulk limit"
    .batteryCVMaxTime_sec = 14400,       //4hrs max CV time (all but lithium)
    .batteryCCRestartThreshold_mV = 12000,  //If below 12v, go from maintenance back to CC (std/agm)
    .batteryMaintenanceOutput_mV = 13150,  //Merged maintenance voltage for std/agm
};

batterychargeparameters_t LithiumChargeParameters =
{
    .batteryChemistry = batteryChemistry_LiFePO,
    .batteryNominalVoltage = nominalBatteryV_12,
    .batteryConstantCurrent_mA = 1000,
    .batteryDetectionLevel_mV = 4000,
    .batteryRecoveryLevel1_mV = 6000,
    .batteryRecoveryLevel2_mV = 9000,
    .batteryRecoveryPeriod1_sec = 120,   //2 minutes
    .batteryRecoveryPeriod2_sec = 300,  //5 minutes
    .batteryCCThreshold_mV = 14500,
    .batteryReturnFromCV2CCThreshold_mV = 14000,
    .batteryCCMaxTime_sec = 259200,      //72hrs "bulk limit"
    .batteryCVMaxTime_sec = 7200,        //2hrs max CV time (lithium)
    .batteryCCRestartThreshold_mV = 13000,  //If below 13v, go from maintenance back to CC (lithium)
    .batteryMaintenanceOutput_mV = 13500,  //Maintenance voltage for lithium
};
