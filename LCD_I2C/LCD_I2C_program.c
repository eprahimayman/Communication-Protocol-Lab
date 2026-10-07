/*
 * LCD_I2C_program.c
 *
 *  Created on: Oct 5, 2026
 *      Author: eprah
 */
#ifndef F_CPU
#define F_CPU 8000000UL
#endif
#include <avr/io.h>
#include <util/delay.h>

#include "../../Mcal/TWI/TWI_interface.h"
#include "LCD_I2C_config.h"
#include "LCD_I2C_interface.h"

#define LCD_CTRL_COMMAND    0x80
#define LCD_CTRL_DATA       0x40

void Lcd_SendInstruction(uint8_t instruction)
{
    uint8_t buf[2] = { LCD_CTRL_COMMAND, instruction };
    TWI_u8WriteBuffer(LCD_I2C_ADDRESS, buf, 2);

    if (instruction <= 0x03) _delay_ms(2);
    else                     _delay_us(50);
}

void Lcd_WriteCharacter(uint8_t Character)
{
    uint8_t buf[2] = { LCD_CTRL_DATA, Character };
    TWI_u8WriteBuffer(LCD_I2C_ADDRESS, buf, 2);
    _delay_us(50);
}

void Lcd_Init(void)
{
    TWI_voidMasterInit();
    _delay_ms(50);

    Lcd_SendInstruction(0x38);
    Lcd_SendInstruction(0x39);
    Lcd_SendInstruction(0x14);
    Lcd_SendInstruction(0x70);
    Lcd_SendInstruction(0x56);
    Lcd_SendInstruction(0x6C);
    _delay_ms(200);
    Lcd_SendInstruction(0x38);
    Lcd_SendInstruction(0x0C);
    Lcd_SendInstruction(0x01);
    Lcd_SendInstruction(0x06);
}

void Lcd_WriteString(uint8_t *string)
{
    while (*string)
    {
        Lcd_WriteCharacter(*string++);
    }
}

void Lcd_Moveto(uint8_t LineNo, uint8_t DigitNo)
{
    uint8_t addr = (LineNo == 0) ? 0x00 : 0x40;
    Lcd_SendInstruction(0x80 | (addr + DigitNo));
}

void Lcd_specialCharacter(uint8_t *string, uint8_t location)
{
    uint8_t i;
    Lcd_SendInstruction(0x40 | ((location & 0x07) * 8));
    for (i = 0; i < 8; i++)
    {
        Lcd_WriteCharacter(string[i]);
    }
    Lcd_SendInstruction(0x80);
}

void LCD_WriteNumber(int32_t Number)
{
    char buf[12];
    uint8_t i = 0;
    uint32_t n;

    if (Number == 0)
    {
        Lcd_WriteCharacter('0');
        return;
    }

    if (Number < 0)
    {
        Lcd_WriteCharacter('-');
        n = (uint32_t)(-(Number + 1)) + 1;
    }
    else
    {
        n = (uint32_t)Number;
    }

    while (n > 0)
    {
        buf[i++] = '0' + (n % 10);
        n /= 10;
    }
    while (i > 0)
    {
        Lcd_WriteCharacter(buf[--i]);
    }
}

