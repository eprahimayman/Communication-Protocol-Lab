/*
 * TWI_program.c
 *
 *  Created on: Oct 5, 2026
 *      Author: eprah
 */
#include <avr/io.h>
#include "TWI_config.h"
#include "TWI_private.h"
#include "TWI_interface.h"

static uint8_t TWI_u8WaitFlag(void)
{
    uint32_t Local_u32Counter = 0;

    while (!(TWCR & (1 << TWINT)))
    {
        if (++Local_u32Counter >= TWI_u32TIMEOUT) return 0;
    }
    return 1;
}

void TWI_voidMasterInit(void)
{
    TWSR = 0x00;   /* prescaler = 1 (·Ê €Ì¯—  TWI_PRESCALER €Ì¯— Â‰« ﬂ„«‰) */
    TWBR = (uint8_t)(((TWI_SYSTEM_FREQUENCY / TWI_SCL_FREQUENCY) - 16) / (2UL * TWI_PRESCALER));
    TWAR = (uint8_t)(TWI_NODE_ADDRESS << 1);
    TWCR = (1 << TWEN);
}

uint8_t TWI_u8SendStartCondition(void)
{
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

    if (!TWI_u8WaitFlag())                          return TWI_TIMEOUT;
    if ((TWSR & TWI_STATUS_MASK) != TWI_START_ACK)  return TWI_START_ERROR;
    return TWI_OK;
}

void TWI_voidSendStopCondition(void)
{
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

uint8_t TWI_u8SendSlaveAddressWithWrite(uint8_t Copy_u8SlaveAddress)
{
    TWDR = (uint8_t)(Copy_u8SlaveAddress << 1);
    TWCR = (1 << TWINT) | (1 << TWEN);

    if (!TWI_u8WaitFlag())                          return TWI_TIMEOUT;
    if ((TWSR & TWI_STATUS_MASK) != TWI_SLA_W_ACK)  return TWI_SLA_W_ERROR;
    return TWI_OK;
}

uint8_t TWI_u8MasterWriteDataByte(uint8_t Copy_u8Data)
{
    TWDR = Copy_u8Data;
    TWCR = (1 << TWINT) | (1 << TWEN);

    if (!TWI_u8WaitFlag())                           return TWI_TIMEOUT;
    if ((TWSR & TWI_STATUS_MASK) != TWI_DATA_W_ACK)  return TWI_DATA_W_ERROR;
    return TWI_OK;
}

uint8_t TWI_u8WriteBuffer(uint8_t Copy_u8SlaveAddress, const uint8_t *Copy_pu8Data, uint8_t Copy_u8Length)
{
    uint8_t Local_u8Error;
    uint8_t i;

    if (Copy_pu8Data == 0) return TWI_NULL_POINTER;

    Local_u8Error = TWI_u8SendStartCondition();
    if (Local_u8Error != TWI_OK) { TWI_voidSendStopCondition(); return Local_u8Error; }

    Local_u8Error = TWI_u8SendSlaveAddressWithWrite(Copy_u8SlaveAddress);
    if (Local_u8Error != TWI_OK) { TWI_voidSendStopCondition(); return Local_u8Error; }

    for (i = 0; i < Copy_u8Length; i++)
    {
        Local_u8Error = TWI_u8MasterWriteDataByte(Copy_pu8Data[i]);
        if (Local_u8Error != TWI_OK) { TWI_voidSendStopCondition(); return Local_u8Error; }
    }

    TWI_voidSendStopCondition();
    return TWI_OK;
}

