/*
 * tempMeasure.c
 *
 *  Created on: Dec 16, 2021
 *      Author: tjose
 */

#include "../Platform_Specific/tempMeasure.h"

#include "../Platform_Specific/adcRead.h"

int cpackTemp = 0;
int pcbaTemp = 0;
uint8_t cellpackBadTemp = 0;
uint8_t pcbaOvertemp = 0;

int readCellpackTemp(void)
{
    setAdcChannel(CELLPACK_TEMP_ADC_CHANNEL);
    uint16_t adcRes = getAvgAdcResults(SAMPLE_AMT);
    uint16_t tempMv = convertAdcValToMv(adcRes);
    //return ((tempMv < MV_AT_0C) && (tempMv > MV_AT_60C));   //Cell pack temperature between 0C and 60C to charge it or jump
    return tempMv;
}

int readPcbaTemp(void)
{
    setAdcChannel(CELLPACK_TEMP_ADC_CHANNEL);
    uint16_t adcRes = getAvgAdcResults(SAMPLE_AMT);
    uint16_t tempMv = convertAdcValToMv(adcRes);
    //return (tempMv > MV_AT_75C);       //pcba temperature below 75C to charge an external battery
    return tempMv;
}


//Charge internal battery - only between 5C and 35C?
//Ask Peter about temperature override for jumping


void checkTemps()
{
    cpackTemp = readCellpackTemp();
    pcbaTemp = readPcbaTemp();

    if(!cellpackBadTemp && (cpackTemp < MV_AT_60C || cpackTemp > MV_AT_0C))
    {
        cellpackBadTemp = 0; //TODO: NTC not installed yet
    }
    else if(cellpackBadTemp && (cpackTemp > MV_AT_55C && cpackTemp < MV_AT_5C))
    {
        cellpackBadTemp = 0;
    }

    if(!pcbaOvertemp && (pcbaTemp < MV_AT_75C))
    {
        pcbaOvertemp = 0; //TODO: NTC not installed yet
    }
    else if(pcbaOvertemp && (pcbaTemp > MV_AT_70C))
    {
        pcbaOvertemp = 0;
    }
}
