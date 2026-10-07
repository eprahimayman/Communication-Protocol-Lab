/*
 * LDR_Config.h
 *
 *  Created on: Oct 1, 2026
 *      Author: eprah
 */

#ifndef HAL_LDR_LDR_CONFIG_H_
#define HAL_LDR_LDR_CONFIG_H_
#include"../../Mcal/Dio/Dio_InterFace.h"
#include"../../Mcal/Dio/Dio_Private.h"
#include"../../Mcal/ADC/ADC_InterFace.h"
#include"../../Mcal/ADC/ADC_Private.h"
#define LdrGroup Dio_GroupA
#define LdrPin   Dio_Pin0
#define Rknown   10000
#define Vcc 	 5
#define R0      15000
#define K       0.6
#endif /* HAL_LDR_LDR_CON
FIG_H_ */
