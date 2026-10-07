/*
 * USART_interface.h
 *
 *  Created on: Oct 5, 2026
 *      Author: eprah
 */

//#ifndef MCAL_USART_USART_INTERFACE_H_
//#define MCAL_USART_USART_INTERFACE_H_
//
//
//
//#endif /* MCAL_USART_USART_INTERFACE_H_ */

/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    USART_interface.h    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author : Mahmoud Karem Zamel
 *  Layer  : MCAL
 *  SWC    : USART
 *
 */

/*File Gard*/
//#ifndef USART_INTERFACE_H_
//#define USART_INTERFACE_H_
//
//
//
//#endif
/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    USART_interface.h    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author : Mahmoud Karem Zamel
 *  Layer   : MCAL
 *  SWC    : USART
 *
 */

/*File Gard*/
/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    USART_interface.h    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author : Mahmoud Karem Zamel
 *  Layer   : MCAL
 *  SWC    : USART
 *
 */

#ifndef USART_INTERFACE_H_
#define USART_INTERFACE_H_

#include <stdint.h>
#include"STD_TYPES.h"
void USART_voidInit (void);

uint8_t USART_u8SendData (uint8_t Copy_u8Data);

uint8_t USART_u8RecevieData (uint8_t * Copy_u8ReceviedData) ;

uint8_t USART_u8SendStringSynch (const uint8_t * Copy_pchString);
uint8_t USART_u8SendStringAsynch (const uint8_t * Copy_pchString , void (* NotificationFunc)(void)) ;

uint8_t USART_u8ReceiveBufferSynch (uint8_t * Copy_pchString , uint32_t Copy_uint32BufferSize) ;
uint8_t USART_u8ReceiveBufferAsynch (uint8_t * Copy_pchString , uint32_t Copy_uint32BufferSize , void (* NotificationFunc)(void)) ;

#endif
