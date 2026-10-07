/*
 * LDR_InterFace.h
 *
 *  Created on: Oct 1, 2026
 *      Author: eprah
 */

#ifndef HAL_LDR_LDR_INTERFACE_H_
#define HAL_LDR_LDR_INTERFACE_H_
#include"LDR_Config.h"
#include"LDR_Private.h"
void Ldr_Init(void);
uint16_t LDR_Read(void);
uint32_t LDR_GetRes(void);
uint32_t LDR_GetLUX(void);
#endif /* HAL_LDR_LDR_INTERFACE_H_ */
