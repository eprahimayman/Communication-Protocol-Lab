/*
 * LCD_I2C_interface.h
 *
 *  Created on: Oct 5, 2026
 *      Author: eprah
 */

#ifndef HAL_LCD_I2C_LCD_I2C_INTERFACE_H_
#define HAL_LCD_I2C_LCD_I2C_INTERFACE_H_

#include <stdint.h>

void Lcd_Init(void);
void Lcd_SendInstruction(uint8_t instruction);
void Lcd_WriteCharacter(uint8_t Character);
void Lcd_WriteString(uint8_t *string);
void Lcd_Moveto(uint8_t LineNo, uint8_t DigitNo);
void Lcd_specialCharacter(uint8_t *string, uint8_t location);
void LCD_WriteNumber(int32_t Number);

#endif /* HAL_LCD_I2C_LCD_I2C_INTERFACE_H_ */
