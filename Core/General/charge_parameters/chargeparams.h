/*
 * chargeparams.h
 *
 *  Created on: Jan 5, 2022
 *      Author: tjose
 */

#ifndef GENERAL_CHARGE_PARAMETERS_CHARGEPARAMS_H_
#define GENERAL_CHARGE_PARAMETERS_CHARGEPARAMS_H_

#include "../General/charging/batterycharging.h"

typedef enum
{
    StdAgmChemistry,
    LithiumChemistry,
} battchemistry_t;

extern battchemistry_t selectedChemistry;

extern batterychargeparameters_t StdAgmChargeParameters;
extern batterychargeparameters_t LithiumChargeParameters;

#endif /* GENERAL_CHARGE_PARAMETERS_CHARGEPARAMS_H_ */
