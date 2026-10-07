/*
 * TWI_interface.h
 *
 *  Created on: Oct 5, 2026
 *      Author: eprah
 */

#ifndef MCAL_TWI_TWI_INTERFACE_H_
#define MCAL_TWI_TWI_INTERFACE_H_

#include <stdint.h>

#define TWI_OK                  0
#define TWI_TIMEOUT             1
#define TWI_START_ERROR         2
#define TWI_SLA_W_ERROR         4
#define TWI_DATA_W_ERROR        6
#define TWI_NULL_POINTER        8

void    TWI_voidMasterInit(void);
uint8_t TWI_u8SendStartCondition(void);
void    TWI_voidSendStopCondition(void);
uint8_t TWI_u8SendSlaveAddressWithWrite(uint8_t Copy_u8SlaveAddress);
uint8_t TWI_u8MasterWriteDataByte(uint8_t Copy_u8Data);
uint8_t TWI_u8WriteBuffer(uint8_t Copy_u8SlaveAddress, const uint8_t *Copy_pu8Data, uint8_t Copy_u8Length);

#endif /* MCAL_TWI_TWI_INTERFACE_H_ */
