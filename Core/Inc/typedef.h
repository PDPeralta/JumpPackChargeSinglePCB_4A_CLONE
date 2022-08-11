/*
 * typedef.h
 *
 *  Created on: Jul 25, 2022
 *      Author: paulp
 */

#ifndef CHARGE_PARAMETERS_TYPEDEF_H_
#define CHARGE_PARAMETERS_TYPEDEF_H_

typedef enum
{
    stRelayTestState,
    stErrorState,           //Present one of several errors on UI and transition out on correct conditions
    stIdle,                 //No AC, no jump, can charge cellpack via USB or charge external accessory from cellpack
    stIdleLowBatt,          //Low internal cell pack, do nothing but charge cellpack via AC or USB in. Prioritize AC charging. Exit to stIdle when sufficient batt
    stIntBattCharging,      //Internal battery is charging either from AC or USB power
    stAcChargerIdle,        //AC plugged in, waiting for ext battery connected, can charge cellpack via AC only
    stAcChargerCharging,    //Charging an external battery (task_charging running)
    stJumpWaitForBatt,      //No AC (indicate if contention), waiting for engine start button pressed then tests for jumping load
    stJumpJumping,          //Jumping an external load (task_jump running)
    stJumpSuccess,          //Jump succeeded

} mainTaskState_t;

#endif /* CHARGE_PARAMETERS_TYPEDEF_H_ */
