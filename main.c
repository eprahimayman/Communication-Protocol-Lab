/*
 * main.c
 *
 *  Created on: Sep 2, 2026
 *      Author: eprah
 */

#include"../Hal/Led/Led_InterFace.h"
#include"../Hal/Lcd/Lcd_InterFace.h"
#include"../Hal/Lcd/Lcd_Private.h"
#include"EXTIApp/EXTIApp_InterFace.h"
#include"../Hal/DCMotor/DC_InterFace.h"
// sender
#define F_CPU 8000000UL
#include <stdint.h>
#include <stdlib.h>
#include <util/delay.h>
#include "../Mcal/USART/USART_interface.h"
#include "../Hal/LDR/LDR_Interface.h"
#include "../Hal/LCD_I2C/LCD_I2C_interface.h"

#define DARK_LUX    50
#define LIGHT_LUX   150


#define LUX_MIN     10
#define LUX_MAX     250

int main(void)
{
    uint32_t lux;
    char isDark = 0;
/*
 * LDR SENSOR CAN'T WORK In SIMULATION
 * */
    Ldr_Init();
    srand(1234);
    USART_voidInit();
    Lcd_Init();

    while (1)
    {
        lux = LUX_MIN + (uint32_t)(rand() % (LUX_MAX - LUX_MIN + 1));   /* random lux */


        if (lux < DARK_LUX)        isDark = 1;
        else if (lux > LIGHT_LUX)  isDark = 0;

        /* I2C LCD */
        Lcd_SendInstruction(Lcd_ClearDisplay);
        _delay_ms(2);

        Lcd_Moveto(0, 0);
        Lcd_WriteString((uint8_t *)"LUX:");
        LCD_WriteNumber((int32_t)lux);

        Lcd_Moveto(1, 0);
        Lcd_WriteString(isDark ? (uint8_t *)"DARK" : (uint8_t *)"LIGHT");

        USART_u8SendData(isDark ? 'D' : 'L');

        _delay_ms(3000);
    }
}

// Reciever
#define LED_GROUP   Dio_GroupB
#define LED_COUNT   8

static void Leds_Set(uint8_t state){
	for(uint8_t i = 0; i < LED_COUNT; i++){
		Led_Init(LED_GROUP, i);
		Dio_WriteValueForPin(LED_GROUP, i, state);
	}
}
#define F_CPU 8000000UL
#include <stdint.h>
#include <stdlib.h>
#include <util/delay.h>
#include "../Mcal/USART/USART_interface.h"
#include "../Hal/LDR/LDR_Interface.h"
int main(void)
{
    u8 data;
    Lcd_Init();
    USART_voidInit();
    while (1)
    {
        if (USART_u8RecevieData(&data) == OK)
        {
            if (data == 'D')
            {
                Lcd_SendInstruction(Lcd_ClearDisplay);
                _delay_ms(2);
                Lcd_WriteString((uint8_t *)"DARK");
                Leds_Set(Source);
            }
            else if (data == 'L')
            {
                Lcd_SendInstruction(Lcd_ClearDisplay);
                _delay_ms(2);
                Lcd_WriteString((uint8_t *)"LIGHT");
                Leds_Set(Sink);
            }
        }
    }
}
