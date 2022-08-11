/*
 * tempMeasure.h
 *
 *  Created on: Dec 16, 2021
 *      Author: tjose
 */

#ifndef PLATFORM_SPECIFIC_TEMPMEASURE_H_
#define PLATFORM_SPECIFIC_TEMPMEASURE_H_

#include "main.h"

#define CELLPACK_TEMP_ADC_CHANNEL   ADC_CHANNEL_1     //Pin to cellpack thermistor divider
#define PCBA_TEMP_ADC_CHANNEL       ADC_CHANNEL_2     //Pin to PCBA thermistor divider

//int cpackTemp;
//int pcbaTemp;
extern uint8_t cellpackBadTemp;
extern uint8_t pcbaOvertemp;

//Based on 100K nominal NTC (NCP18WF104F12RB) paired with 100K resistor Vcc--100k--NTC--GND
//Datasheet - https://www.murata.com/en-eu/api/pdfdownloadapi?cate=&partno=NCP18WF104F12RB

#define MV_AT_0C     2566    //NTC @ ~350Kohm
#define MV_AT_5C     2475    //NTC @ ~300Kohm
#define MV_AT_25C    1650    //NTC @ ~100Kohm (nominal value)
#define MV_AT_50C    762     //NTC @ ~30Kohm
#define MV_AT_55C    660     //NTC @ ~25Kohm
#define MV_AT_60C    550     //NTC @ ~20Kohm
#define MV_AT_70C    430     //NTC @ ~15Kohm
#define MV_AT_75C    380     //NTC @ ~13Kohm

int readCellpackTemp(void);
int readPcbaTemp(void);

void checkTemps();

#endif /* PLATFORM_SPECIFIC_TEMPMEASURE_H_ */
