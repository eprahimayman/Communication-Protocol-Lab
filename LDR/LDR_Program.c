/*
 * LDR_Program.c
 *
 *  Created on: Oct 1, 2026
/*
 * LDR_Program.c
 *
 *  Created on: Oct 1, 2026
 *      Author: eprah
 */
#include "LDR_InterFace.h"


void Ldr_Init(void){
	Dio_DirectionSetForPin(LdrGroup, LdrPin, Dio_InPut);
	ADC_Init();
}


uint16_t LDR_Read(){
	return ADC_GetDigitalVolt(LdrPin,100);
}

static float Ldr_Cbrt(float x){
    float y = 1.0;
    uint8_t i;
    for (i = 0; i < 12; i++) {
        y = (2.0 * y + x / (y * y)) / 3.0;
    }
    return y;
}
uint32_t LDR_GetRes(void){
    uint16_t digital = LDR_Read();

    if (digital >= 1023) return 0;
    if (digital == 0)    return 0xFFFFFFFF;

    return ((uint32_t)Rknown * (1023UL - digital)) / digital;
}

uint32_t LDR_GetLUX(void){

    uint32_t resistance = LDR_GetRes();
    if (resistance == 0xFFFFFFFF) return 0;
    if (resistance == 0) {
        return 100000;
    }

    float x = (float)R0 / (float)resistance;
    float lux = 10.0 * (x * x) / Ldr_Cbrt(x);
    return (uint32_t)lux;
}


